#pragma once
#include "globals.h"

#include "proxy_bridge.h"
#include "observes.h"

template<typename MasterDomain, typename SlaveDomain>
class DataProxy : public Observes<MasterDomain> {

protected:
    USING_REACTIVE_DOMAIN(SlaveDomain)

public:
    DataProxy(weak_ptr<void> master_, ProxyBridge& proxyBridge_)
        : master(master_)
        , proxyBridge(proxyBridge_)
    {
    }

protected:
    template<typename T>
    void bindSignal(Signal<MasterDomain, T> masterSignal, VarSignal<SlaveDomain, T> slaveSignal);

    template<typename T>
    void bindEvent(Events<MasterDomain, shared_ptr<T>>& masterEvent, EventSource<SlaveDomain, shared_ptr<T>>& slaveEvent);
    template<typename T>
    void bindEvent(Events<MasterDomain, T> masterEvent, EventSource<SlaveDomain, T> slaveEvent);

    template<typename C>
    void sendCommand(function<void(shared_ptr<C>)> func);

    template<typename C, typename R>
    void sendCommand(function<R(shared_ptr<C>)> func, function<void(R)> response);

private:
    weak_ptr<void> master;

    ProxyBridge& proxyBridge;

};

// template<typename P, typename O>
// unique_ptr<P> makeProxy(weak_ptr<O> object) {
//     return makeProxy(object);
// }

#include "data_proxy.tpp"
