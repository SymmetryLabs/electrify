template<typename MasterDomain, typename SlaveDomain>
template<typename T>
void DataProxy<MasterDomain, SlaveDomain>::bindSignal(Signal<MasterDomain, T> masterSignal, VarSignal<SlaveDomain, T> slaveSignal)
{
  this->addObserver(Observe(masterSignal, [&] (T object) {
    proxyBridge.queueDownstreamEvent([=, &slaveSignal] {
      cout << "ok8" << endl;
      slaveSignal <<= object;
    });
  }));
}

template<typename MasterDomain, typename SlaveDomain>
template<typename T>
void DataProxy<MasterDomain, SlaveDomain>::bindEvent(Events<MasterDomain, shared_ptr<T>>& masterEvent, EventSource<SlaveDomain, shared_ptr<T>>& slaveEvent)
{
  cout << "test" << endl;
  // Events<MasterDomain, shared_ptr<T>> processedEvent = Process<shared_ptr<T>, string>(masterEvent,
  //   [](EventRange<shared_ptr<T>> range, EventEmitter<shared_ptr<T>> out) {
  //   for (shared_ptr<T>& object : range) {
  //     out.emit(makeProxy(object));
  //   }
  // });
  // MakeContinuation<MasterDomain, SlaveSyncDomain>(processedEvent,
  //   [&] (shared_ptr<T> object) {
  //   slaveEvent.emit(object);
  // });
}

template<typename MasterDomain, typename SlaveDomain>
template<typename T>
void DataProxy<MasterDomain, SlaveDomain>::bindEvent(Events<MasterDomain, T> masterEvent, EventSource<SlaveDomain, T> slaveEvent)
{
  cout << "test2" << endl;
  // downstreamContinuations.push_back(MakeContinuation<MasterDomain, SlaveSyncDomain>(masterEvent,
  //   [&] (T object) {
  //   cout << "ok9" << endl;
  //   slaveEvent << object;
  // }));
}

template<typename MasterDomain, typename SlaveDomain>
template<typename C>
void DataProxy<MasterDomain, SlaveDomain>::sendCommand(function<void(shared_ptr<C>)> func)
{
  weak_ptr<void> localWeakMaster = master;
  proxyBridge.queueUpstreamEvent([=] {
    if (auto strongMaster = localWeakMaster.lock()) {
      func(static_pointer_cast<C>(strongMaster));
    }
  });
}

template<typename MasterDomain, typename SlaveDomain>
template<typename C, typename R>
void DataProxy<MasterDomain, SlaveDomain>::sendCommand(function<R(shared_ptr<C>)> func, function<void(R)> response)
{
  weak_ptr<void> localWeakMaster = master;
  proxyBridge.queueUpstreamEvent([=] {
    if (auto strongMaster = localWeakMaster.lock()) {
      R rtn = func(static_pointer_cast<C>(strongMaster));

      proxyBridge.queueDownstreamEvent([=] {
        response(rtn);
      });
    }
  });
}
