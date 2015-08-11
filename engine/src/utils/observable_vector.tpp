template<typename D, typename T, typename MasterDomain>
void ObservableVector<D, T, MasterDomain>::clear()
{
  while (size() > 0) {
    pop_back();
  }
}

template<typename D, typename T, typename MasterDomain>
typename vector<T>::iterator ObservableVector<D, T, MasterDomain>::insert(typename vector<T>::const_iterator pos, const T& value)
{
  size_t i = pos - v.begin();
  typename vector<T>::iterator rtn = v.insert(pos, value);
  valueAdded(make_pair<size_t, reference_wrapper<T>>(move(i), ref(v[i])));
  return rtn;
}

template<typename D, typename T, typename MasterDomain>
typename vector<T>::iterator ObservableVector<D, T, MasterDomain>::insert(typename vector<T>::const_iterator pos, T&& value)
{
  size_t i = pos - v.begin();
  typename vector<T>::iterator rtn = v.insert(pos, forward<T>(value));
  valueAdded(make_pair<size_t, reference_wrapper<T>>(move(i), ref(v[i])));
  return rtn;
}

template<typename D, typename T, typename MasterDomain>
typename vector<T>::iterator ObservableVector<D, T, MasterDomain>::erase(typename vector<T>::iterator pos)
{
  size_t i = pos - v.begin();
  T value = move(*pos);
  typename vector<T>::iterator rtn = v.erase(pos);
  valueRemoved(make_pair<size_t, T>(move(i), move(value)));
  return rtn;
}

template<typename D, typename T, typename MasterDomain>
typename vector<T>::iterator ObservableVector<D, T, MasterDomain>::erase(typename vector<T>::const_iterator pos)
{
  size_t i = pos - v.begin();
  T value = move(*pos);
  typename vector<T>::iterator rtn = v.erase(pos);
  valueRemoved(make_pair<size_t, T>(i, move(value)));
  return rtn;
}

template<typename D, typename T, typename MasterDomain>
void ObservableVector<D, T, MasterDomain>::push_back(const T& value)
{
  v.push_back(value);
  valueAdded(make_pair<size_t, reference_wrapper<T>>(size() - 1, ref(back())));
}

template<typename D, typename T, typename MasterDomain>
void ObservableVector<D, T, MasterDomain>::push_back(T&& value)
{
  v.push_back(forward<T>(value));
  valueAdded << make_pair<size_t, reference_wrapper<T>>(size() - 1, ref(back()));
}

template<typename D, typename T, typename MasterDomain>
void ObservableVector<D, T, MasterDomain>::pop_back()
{
  T value = move(v.back());
  v.pop_back();
  valueRemoved(make_pair<size_t, T>(size(), move(value)));
}

template<typename D, typename T, typename MasterDomain>
template<typename SlaveDomain>
void ObservableVector<D, T, MasterDomain>
  ::makeProxySlave(ObservableVector<SlaveDomain, T, D>& slave, ProxyBridge& proxyBridge)
{
  for (T& obj : v) {
    slave.push_back(obj);
  }

  slave.masterAddedValueEvent = Process<pair<size_t, T>>(valueAdded,
    [&](EventRange<pair<size_t, reference_wrapper<T>>> range, EventEmitter<pair<size_t, T>> out) {
    for (pair<size_t, reference_wrapper<T>> object : range) {
      out = make_pair(object.first, object.second.get());
    }
  });
  slave.addObserver(Observe(slave.masterAddedValueEvent, [&] (pair<size_t, T> p) {
    proxyBridge.queueDownstreamEvent([=, &slave] {
      slave.insert(slave.begin() + p.first, p.second);
    });
  }));

  slave.addObserver(Observe(valueRemoved, [&] (pair<size_t, T> p) {
    proxyBridge.queueDownstreamEvent([=, &slave] {
      slave.erase(slave.begin() + p.first);
    });
  }));
}

template<typename D, typename T, typename MasterDomain>
template<typename SlaveDomain, typename SlaveType>
void ObservableVector<D, T, MasterDomain>
  ::makeProxySlave(ObservableVector<SlaveDomain, shared_ptr<SlaveType>, D>& slave, ProxyBridge& proxyBridge)
{
  for (T& obj : v) {
    slave.push_back(makeProxy<SlaveDomain>(obj, proxyBridge));
  }

  slave.masterAddedValueEvent = Process<pair<size_t, shared_ptr<SlaveType>>>(valueAdded,
    [&](EventRange<pair<size_t, reference_wrapper<T>>> range, EventEmitter<pair<size_t, shared_ptr<SlaveType>>> out) {
    for (pair<size_t, reference_wrapper<T>> object : range) {
      out = make_pair(object.first, makeProxy<SlaveDomain>(object.second.get(), proxyBridge));
    }
  });
  slave.addObserver(Observe(slave.masterAddedValueEvent, [&] (pair<size_t, shared_ptr<SlaveType>> p) {
    proxyBridge.queueDownstreamEvent([=, &slave] {
      slave.insert(slave.begin() + p.first, p.second);
    });
  }));

  slave.addObserver(Observe(valueRemoved, [&] (pair<size_t, T> p) {
    proxyBridge.queueDownstreamEvent([=, &slave] {
      slave.erase(slave.begin() + p.first);
    });
  }));
}
