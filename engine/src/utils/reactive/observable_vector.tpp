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
    ::makeProxySlave(ObservableVector<T>& slave, ProxyBridge& proxyBridge) const
{
    for (const auto& obj : v) {
        slave.push_back(obj);
    }

    auto masterAddedValueEvent = valueAdded.map(
        [&](const std::pair<size_t, std::reference_wrapper<const T>>& object) {
        return std::make_pair(object.first, object.second.get());
    });
    slave.observe(masterAddedValueEvent, [&] (std::pair<size_t, T> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.insert(slave.begin() + p.first, p.second);
        });
    });

    slave.observe(valueRemoved, [&] (size_t pos) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.erase(slave.begin() + pos);
        });
    });
}

template<typename T>
template<typename SlaveType>
void ObservableVector<T>
    ::makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ProxyBridge& proxyBridge) const
{
    for (const auto& obj : v) {
        slave.push_back(obj->template getProxy<SlaveType>(proxyBridge));
    }

    auto masterAddedValueEvent = valueAdded.map(
        [&](const std::pair<size_t, std::reference_wrapper<const T>>& object) {
        return std::make_pair(object.first,
            object.second.get()->template getProxy<SlaveType>(proxyBridge));
    });
    slave.observe(masterAddedValueEvent,
        [&] (std::pair<size_t, std::shared_ptr<SlaveType>> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.insert(slave.begin() + p.first, p.second);
        });
    });

    slave.observe(valueRemoved, [&] (size_t pos) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.erase(slave.begin() + pos);
        });
    });
}

template<typename T>
template<typename SlaveType, typename... ArgN>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ArgN&&... args) const
        -> typename std::enable_if<!std::is_convertible<typename std::tuple_element<0, std::tuple<ArgN...> >::type, std::function<std::shared_ptr<SlaveType>(T)>>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(std::make_shared<SlaveType>(*obj.get(), std::forward<ArgN>(args)...));
    }

    slave.observe(valueAdded,
        [&slave, &args...] (const std::pair<size_t, std::reference_wrapper<const T>>& object) {
        slave.insert(slave.begin() + object.first,
            std::make_shared<SlaveType>(*object.second.get().get(),
                std::forward<ArgN>(args)...));
    });

    slave.observe(valueRemoved, [&] (size_t pos) {
        slave.erase(slave.begin() + pos);
    });
}

template<typename T>
template<typename SlaveType, typename FCreate, typename FDestr>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, FCreate&& createFunc, FDestr&& destructFunc) const
        -> typename std::enable_if<std::is_convertible<FCreate, std::function<std::shared_ptr<SlaveType>(T)>>::value
                                    && std::is_convertible<FDestr, std::function<void(std::shared_ptr<SlaveType>)>>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(createFunc(obj));
    }

    slave.observe(valueAdded,
        [&, createFunc] (const std::pair<size_t, std::reference_wrapper<const T>>& p) {
        slave.insert(slave.begin() + p.first, createFunc(p.second.get()));
    });

    slave.observe(valueRemoved, [&, destructFunc] (size_t pos) {
        std::shared_ptr<SlaveType> removed = slave[pos];
        slave.erase(slave.begin() + pos);
        destructFunc(removed);
    });
}
