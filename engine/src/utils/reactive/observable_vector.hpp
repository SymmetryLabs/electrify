template<typename T, typename Alloc>
ObservableVector<T, Alloc>::~ObservableVector()
{
    ObjectOwner::releaseAll();
}

template<typename T, typename Alloc>
ObservableVector<T, Alloc>& ObservableVector<T, Alloc>::operator=(const std::vector<T, Alloc>& x)
{
    while (v.size() > 0) {
        willRemoveValue(std::ref<T>(v.back()));
        v.pop_back();
        valueRemoved(v.size());
    }
    for (const T& t : x) {
        v.push_back(t);
        valueAdded(std::make_pair(v.size() - 1, std::ref<T>(v.back())));
    }
    sizeVar = v.size();
    return *this;
}

template<typename T, typename Alloc>
ObservableVector<T, Alloc>& ObservableVector<T, Alloc>::operator=(std::initializer_list<value_type> il)
{
    while (v.size() > 0) {
        willRemoveValue(std::ref<T>(v.back()));
        v.pop_back();
        valueRemoved(v.size());
    }
    for (value_type t : il) {
        v.push_back(t);
        valueAdded(std::make_pair(v.size() - 1, std::ref<T>(v.back())));
    }
    sizeVar = v.size();
    return *this;
}

template<typename T, typename Alloc>
void ObservableVector<T, Alloc>::push_back(const T& value)
{
    v.push_back(value);
    valueAdded(std::make_pair(size() - 1, std::ref<T>(v.back())));
    sizeVar = v.size();
}

template<typename T, typename Alloc>
void ObservableVector<T, Alloc>::push_back(T&& value)
{
    v.push_back(std::forward<T>(value));
    valueAdded(std::make_pair(size() - 1, std::ref<T>(v.back())));
    sizeVar = v.size();
}

template<typename T, typename Alloc>
void ObservableVector<T, Alloc>::pop_back()
{
    willRemoveValue(std::ref<T>(v.back()));
    v.pop_back();
    valueRemoved(size());
    sizeVar = v.size();
}

template<typename T, typename Alloc>
typename std::vector<T, Alloc>::iterator ObservableVector<T, Alloc>::insert(const_iterator pos, const T& value)
{
    auto i = pos - v.begin();
    auto rtn = v.insert(pos, value);
    valueAdded(std::make_pair(std::move(i), std::ref<T>(v[i])));
    sizeVar = v.size();
    return rtn;
}

template<typename T, typename Alloc>
typename std::vector<T, Alloc>::iterator ObservableVector<T, Alloc>::insert(const_iterator pos, T&& value)
{
    auto i = pos - v.begin();
    auto rtn = v.insert(pos, std::forward<T>(value));
    valueAdded(std::make_pair(std::move(i), std::ref<T>(v[i])));
    sizeVar = v.size();
    return rtn;
}

template<typename T, typename Alloc>
typename std::vector<T, Alloc>::iterator ObservableVector<T, Alloc>::erase(iterator pos)
{
    auto i = pos - v.begin();
    willRemoveValue(std::ref<T>(v.at(i)));
    auto rtn = v.erase(pos);
    valueRemoved(i);
    sizeVar = v.size();
    return rtn;
}

template<typename T, typename Alloc>
typename std::vector<T, Alloc>::iterator ObservableVector<T, Alloc>::erase(const_iterator pos)
{
    auto i = pos - v.begin();
    willRemoveValue(std::ref<T>(v.at(i)));
    auto rtn = v.erase(pos);
    valueRemoved(i);
    sizeVar = v.size();
    return rtn;
}

template<typename T, typename Alloc>
void ObservableVector<T, Alloc>::clear()
{
    while (v.size() > 0) {
        willRemoveValue(std::ref<T>(v.back()));
        v.pop_back();
        valueRemoved(v.size());
    }
    sizeVar = v.size();
}

template<typename T, typename Alloc>
void ObservableVector<T, Alloc>
    ::makeProxySlave(ObservableVector<T, Alloc>& slave, DataProxy& dataProxy) const
{
    for (const auto& obj : v) {
        slave.push_back(obj);
    }

    slave.scopedObserve(valueAdded,
        [&] (const std::pair<size_t, std::reference_wrapper<T>>& p) {
        size_t pos = p.first;
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

template<typename T, typename Alloc>
template<typename SlaveType, typename SlaveAlloc>
void ObservableVector<T, Alloc>
    ::makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave, DataProxy& dataProxy) const
{
    for (const auto& obj : v) {
        slave.push_back(obj->template getSlave<SlaveType>());
    }

    slave.scopedObserve(valueAdded,
        [&] (const std::pair<size_t, std::reference_wrapper<T>>& p) {
        size_t pos = p.first;
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

template<typename T, typename Alloc>
template<typename SlaveType, typename... ArgN, typename SlaveAlloc>
auto ObservableVector<T, Alloc>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave, ArgN&&... args) const
        -> typename std::enable_if<!is_callable<typename std::tuple_element<0, std::tuple<ArgN...> >::type, T>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(std::make_shared<SlaveType>(*obj.get(), std::forward<ArgN>(args)...));
    }

    slave.scopedObserve(valueAdded,
        [&slave, &args...] (const std::pair<size_t, std::reference_wrapper<T>>& object) {
        slave.insert(slave.begin() + object.first,
            std::make_shared<SlaveType>(*object.second.get().get(),
                std::forward<ArgN>(args)...));
    });

    slave.scopedObserve(valueRemoved, [&] (size_t pos) {
        slave.erase(slave.begin() + pos);
    });
}

template<typename T, typename Alloc>
template<typename SlaveType, typename FCreate, typename FDestr, typename SlaveAlloc>
auto ObservableVector<T, Alloc>
    ::makeSlave(ObservableVector<std::shared_ptr<SlaveType>, SlaveAlloc>& slave,
        FCreate&& createFunc, FDestr&& destructFunc) const
        -> typename std::enable_if<is_callable<FCreate, T>::value &&
            is_callable<FDestr, std::shared_ptr<SlaveType>>::value>::type
{
    for (const auto& obj : v) {
        slave.push_back(createFunc(obj));
    }

    slave.scopedObserve(valueAdded,
        [&, createFunc] (const std::pair<size_t, std::reference_wrapper<T>>& p) {
        slave.insert(slave.begin() + p.first, createFunc(p.second.get()));
    });

    slave.scopedObserve(valueRemoved, [&, destructFunc] (size_t pos) {
        std::shared_ptr<SlaveType> removed = slave[pos];
        slave.erase(slave.begin() + pos);
        destructFunc(removed);
    });
}
