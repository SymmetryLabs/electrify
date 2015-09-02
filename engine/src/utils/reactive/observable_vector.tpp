template<typename T>
void ObservableVector<T>::clear()
{
    while (size() > 0) {
        pop_back();
    }
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::insert(typename std::vector<T>::const_iterator pos, const T& value)
{
    size_t i = pos - v.begin();
    typename std::vector<T>::iterator rtn = v.insert(pos, value);
    valueAdded(std::make_pair<size_t, std::reference_wrapper<T>>(move(i), ref(v[i])));
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::insert(typename std::vector<T>::const_iterator pos, T&& value)
{
    size_t i = pos - v.begin();
    typename std::vector<T>::iterator rtn = v.insert(pos, std::forward<T>(value));
    valueAdded(std::make_pair<size_t, std::reference_wrapper<T>>(move(i), ref(v[i])));
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::erase(typename std::vector<T>::iterator pos)
{
    size_t i = pos - v.begin();
    T value = std::move(*pos);
    typename std::vector<T>::iterator rtn = v.erase(pos);
    valueRemoved(std::make_pair<size_t, T>(std::move(i), std::move(value)));
    return rtn;
}

template<typename T>
typename std::vector<T>::iterator ObservableVector<T>::erase(typename std::vector<T>::const_iterator pos)
{
    size_t i = pos - v.begin();
    T value = std::move(*pos);
    typename std::vector<T>::iterator rtn = v.erase(pos);
    valueRemoved(std::make_pair<size_t, T>(i, std::move(value)));
    return rtn;
}

template<typename T>
void ObservableVector<T>::push_back(const T& value)
{
    v.push_back(value);
    valueAdded(std::make_pair<size_t, std::reference_wrapper<T>>(size() - 1, std::ref(back())));
}

template<typename T>
void ObservableVector<T>::push_back(T&& value)
{
    v.push_back(std::forward<T>(value));
    valueAdded(std::make_pair<size_t, std::reference_wrapper<T>>(size() - 1, std::ref(back())));
}

template<typename T>
void ObservableVector<T>::pop_back()
{
    T value = std::move(v.back());
    v.pop_back();
    valueRemoved(make_pair<size_t, T>(size(), std::move(value)));
}

template<typename T>
void ObservableVector<T>
    ::makeProxySlave(ObservableVector<T>& slave, ProxyBridge& proxyBridge)
{
    for (T& obj : v) {
        slave.push_back(obj);
    }

    auto masterAddedValueEvent = valueAdded.map(
        [&](const std::pair<size_t, std::reference_wrapper<T>>& object) {
        return std::make_pair(object.first, object.second.get());
    });
    slave.observe(masterAddedValueEvent, [&] (std::pair<size_t, T> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.insert(slave.begin() + p.first, p.second);
        });
    });

    slave.observe(valueRemoved, [&] (std::pair<size_t, T> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.erase(slave.begin() + p.first);
        });
    });
}

template<typename T>
template<typename SlaveType>
void ObservableVector<T>
    ::makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ProxyBridge& proxyBridge)
{
    for (T& obj : v) {
        slave.push_back(obj->template getProxy<SlaveType>(proxyBridge));
    }

    auto masterAddedValueEvent = valueAdded.map(
        [&](const std::pair<size_t, std::reference_wrapper<T>>& object) {
        return std::make_pair(object.first,
            object.second.get()->template getProxy<SlaveType>(proxyBridge));
    });
    slave.observe(masterAddedValueEvent,
        [&] (std::pair<size_t, std::shared_ptr<SlaveType>> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.insert(slave.begin() + p.first, p.second);
        });
    });

    slave.observe(valueRemoved, [&] (std::pair<size_t, T> p) {
        proxyBridge.queueDownstreamEvent([=, &slave] {
            slave.erase(slave.begin() + p.first);
        });
    });
}

template<typename T>
template<typename SlaveType, typename... ArgN>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ArgN&&... args)
        -> typename std::enable_if<!std::is_convertible<typename std::tuple_element<0, std::tuple<ArgN...> >::type, std::function<std::shared_ptr<SlaveType>(T)>>::value>::type
{
    for (T& obj : v) {
        slave.push_back(std::make_shared<SlaveType>(*obj.get(), std::forward<ArgN>(args)...));
    }

    auto masterAddedValueEvent = valueAdded.map(
        [&args...] (std::pair<size_t, std::reference_wrapper<T>> object) {
        return std::make_pair(object.first,
            std::make_shared<SlaveType>(*object.second.get().get(),
                std::forward<ArgN>(args)...));
    });
    slave.observe(masterAddedValueEvent,
        [&] (std::pair<size_t, std::shared_ptr<SlaveType>> p) {
        slave.insert(slave.begin() + p.first, p.second);
    });

    slave.observe(valueRemoved, [&] (std::pair<size_t, T> p) {
        slave.erase(slave.begin() + p.first);
    });
}

template<typename T>
template<typename SlaveType, typename FCreate, typename FDestr>
auto ObservableVector<T>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, FCreate&& createFunc, FDestr&& destructFunc)
        -> typename std::enable_if<std::is_convertible<FCreate, std::function<std::shared_ptr<SlaveType>(T)>>::value
                                    && std::is_convertible<FDestr, std::function<void(std::shared_ptr<SlaveType>)>>::value>::type
{
    for (T& obj : v) {
        slave.push_back(createFunc(obj));
    }

    slave.observe(valueAdded,
        [&, createFunc] (const std::pair<size_t, std::reference_wrapper<T>>& p) {
        slave.insert(slave.begin() + p.first, createFunc(p.second.get()));
    });

    slave.observe(valueRemoved, [&, destructFunc] (std::pair<size_t, T> p) {
        std::shared_ptr<SlaveType> removed = slave[p.first];
        slave.erase(slave.begin() + p.first);
        destructFunc(removed);
    });
}
