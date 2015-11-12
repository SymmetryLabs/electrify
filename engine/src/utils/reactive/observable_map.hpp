template <typename KeyT, typename ValueT>
std::pair<typename std::map<KeyT, ValueT>::iterator,bool> ObservableMap<KeyT, ValueT>::insert (const value_type& val)
{
    auto rtn = m.insert(val);
    if (rtn.second) {
        valueAdded(*rtn.first);
    }
    return rtn;
}

template <typename KeyT, typename ValueT>
template <class P>
std::pair<typename std::map<KeyT, ValueT>::iterator,bool> ObservableMap<KeyT, ValueT>::insert (P&& val)
{
    auto rtn = m.insert(std::forward<P>(val));
    if (rtn.second) {
        valueAdded(*rtn.first);
    }
    return rtn;
}

template <typename KeyT, typename ValueT>
typename std::map<KeyT, ValueT>::iterator ObservableMap<KeyT, ValueT>::erase (const_iterator position)
{
    auto k = position->first;
    auto rtn = m.erase(position);
    valueRemoved(k);
    return rtn;
}

template <typename KeyT, typename ValueT>
typename std::map<KeyT, ValueT>::size_type ObservableMap<KeyT, ValueT>::erase (const key_type& k)
{
    auto rtn = m.erase(k);
    valueRemoved(k);
    return rtn;
}

template <typename KeyT, typename ValueT>
void ObservableMap<KeyT, ValueT>::clear() noexcept
{
    for (auto iter = m.begin(); iter != m.end(); ) {
        iter = this->erase(iter);
    }
}

template <typename KeyT, typename ValueT>
void ObservableMap<KeyT, ValueT>
    ::makeProxySlave(ObservableMap<KeyT, ValueT>& slave, DataProxy& dataProxy) const
{
    for (const auto& obj : m) {
        slave.insert(obj);
    }

    slave.scopedObserve(valueAdded,
        [&dataProxy, &slave] (const std::pair<const KeyT, ValueT>& object) {
            dataProxy.sendEvent([=, &slave] {
                slave.insert(object);
            });
        }
    );

    slave.scopedObserve(valueRemoved, [&dataProxy, &slave] (const KeyT& key) {
        dataProxy.sendEvent([=, &slave] {
            slave.erase(key);
        });
    });
}
