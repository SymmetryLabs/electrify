template<typename T>
void ObservableVector<T>::push_back(const T& value)
{
    v.push_back(value);
    valueAdded(std::make_pair(size() - 1, std::ref<const T>(back())));
}

template<typename T>
void ObservableVector<T>::push_back(T&& value)
{
    v.push_back(std::forward<T>(value));
    valueAdded(std::make_pair(size() - 1, std::ref<const T>(back())));
}

template<typename T>
void ObservableVector<T>::pop_back()
{
    v.pop_back();
    valueRemoved(size());
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::insert(const_iterator pos, const T& value)
{
    auto i = pos - v.begin();
    auto rtn = v.insert(pos, value);
    valueAdded(std::make_pair(std::move(i), std::ref<const T>(v[i])));
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::insert(const_iterator pos, T&& value)
{
    auto i = pos - v.begin();
    auto rtn = v.insert(pos, std::forward<T>(value));
    valueAdded(std::make_pair(std::move(i), std::ref<const T>(v[i])));
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::erase(iterator pos)
{
    auto i = pos - v.begin();
    auto rtn = v.erase(pos);
    valueRemoved(i);
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::erase(const_iterator pos)
{
    auto i = pos - v.begin();
    auto rtn = v.erase(pos);
    valueRemoved(i);
    return rtn;
}

template<typename T>
void ObservableVector<T>::clear()
{
    while (size() > 0) {
        pop_back();
    }
}

template<typename T>
void ObservableVector<T>
    ::makeProxySlave(ObservableVector<T>& slave, DataProxy& dataProxy) const
{
    for (const auto& obj : v) {
        slave.push_back(obj);
    }

    slave.scopedObserve(valueAdded,
        [&] (const std::pair<size_t, std::reference_wrapper<const T>>& p) {
        const size_t& pos = p.first;
        const T& obj = p.second.get();
        dataProxy.sendEvent([=, &slave] {
            slave.insert(slave.begin() + pos, obj);
        });
    });

    slave.scopedObserve(valueRemoved, [&] (size_t pos) {
        dataProxy.sendEvent([=, &slave] {
            slave.erase(slave.begin() + pos);
        });
    });
}

template<typename T>
template<typename SlaveType>
void ObservableVector<T>
    ::makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, DataProxy& dataProxy) const
{
    for (const auto& obj : v) {
        slave.push_back(obj->template getSlave<SlaveType>());
    }

    slave.scopedObserve(valueAdded,
        [&] (const std::pair<size_t, std::reference_wrapper<const T>>& p) {
        const size_t& pos = p.first;
        std::shared_ptr<SlaveType> obj =
            p.second.get()->template getSlave<SlaveType>();
        dataProxy.sendEvent([=, &slave] {
            slave.insert(slave.begin() + pos, obj);
        });
    });

    slave.scopedObserve(valueRemoved, [&] (size_t pos) {
        dataProxy.sendEvent([=, &slave] {
            slave.erase(slave.begin() + pos);
        });
    });
}

template<typename T>
template<typename SlaveType, typename... ArgN>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ArgN&&... args) const
        -> typename std::enable_if<!is_callable<typename std::tuple_element<0, std::tuple<ArgN...> >::type, T>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(std::make_shared<SlaveType>(*obj.get(), std::forward<ArgN>(args)...));
    }

    slave.scopedObserve(valueAdded,
        [&slave, &args...] (const std::pair<size_t, std::reference_wrapper<const T>>& object) {
        slave.insert(slave.begin() + object.first,
            std::make_shared<SlaveType>(*object.second.get().get(),
                std::forward<ArgN>(args)...));
    });

    slave.scopedObserve(valueRemoved, [&] (size_t pos) {
        slave.erase(slave.begin() + pos);
    });
}

template<typename T>
template<typename SlaveType, typename FCreate, typename FDestr>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave,
        FCreate&& createFunc, FDestr&& destructFunc) const
        -> typename std::enable_if<is_callable<FCreate, T>::value &&
            is_callable<FDestr, std::shared_ptr<SlaveType>>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(createFunc(obj));
    }

    slave.scopedObserve(valueAdded,
        [&, createFunc] (const std::pair<size_t, std::reference_wrapper<const T>>& p) {
        slave.insert(slave.begin() + p.first, createFunc(p.second.get()));
    });

    slave.scopedObserve(valueRemoved, [&, destructFunc] (size_t pos) {
        std::shared_ptr<SlaveType> removed = slave[pos];
        slave.erase(slave.begin() + pos);
        destructFunc(removed);
    });
}
