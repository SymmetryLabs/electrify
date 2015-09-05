template<typename T>
void DataProxy::bind(Observable<T>& masterSignal, TokenSource<T>& slaveSignal)
{
    observe(masterSignal, [&] (T object) {
        proxyBridge.queueDownstreamEvent([=, &slaveSignal] {
            slaveSignal << object;
        });
    });
}

template<typename C>
void DataProxy::sendCommand(std::function<void(std::shared_ptr<C>)> func)
{
    std::weak_ptr<void> localWeakMaster = master;
    proxyBridge.queueUpstreamEvent([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            func(std::static_pointer_cast<C>(strongMaster));
        }
    });
}

template<typename C, typename S1, typename T1>
void DataProxy::sendCommand(std::function<void(std::shared_ptr<C>, std::shared_ptr<S1>)> func, T1 t1)
{
    std::weak_ptr<void> localWeakMaster = master;
    auto weakT1 = t1.getMaster();
    proxyBridge.queueUpstreamEvent([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = weakT1.lock()) {
                func(std::static_pointer_cast<C>(strongMaster),
                    std::static_pointer_cast<S1>(strongT1));
            }
        }
    });
}

template<typename C, typename S1, typename S2, typename T1, typename T2>
void DataProxy::sendCommand(std::function<void(std::shared_ptr<C>, std::shared_ptr<S1>, std::shared_ptr<S2>)> func, T1 t1, T2 t2)
{
    std::weak_ptr<void> localWeakMaster = master;
    auto weakT1 = t1.getMaster();
    auto weakT2 = t2.getMaster();
    proxyBridge.queueUpstreamEvent([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            if (auto strongT1 = weakT1.lock()) {
                if (auto strongT2 = weakT2.lock()) {
                    func(std::static_pointer_cast<C>(strongMaster),
                        std::static_pointer_cast<S1>(strongT1),
                        std::static_pointer_cast<S2>(strongT2));
                }
            }
        }
    });
}

template<typename C, typename R>
void DataProxy::sendCommand(std::function<R(std::shared_ptr<C>)> func, std::function<void(R)> response)
{
    std::weak_ptr<void> localWeakMaster = master;
    proxyBridge.queueUpstreamEvent([=] {
        if (auto strongMaster = localWeakMaster.lock()) {
            R rtn = func(std::static_pointer_cast<C>(strongMaster));

            proxyBridge.queueDownstreamEvent([=] {
                response(rtn);
            });
        }
    });
}
