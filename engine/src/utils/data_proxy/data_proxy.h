#pragma once

#include <functional>
#include <memory>

#include "proxy_bridge.h"
#include "observes.h"
#include "observable.h"
#include "token_source.h"

class DataProxy : public Observes {

public:
    DataProxy(std::weak_ptr<void> master, ProxyBridge& proxyBridge);
    
    std::weak_ptr<void> getMaster() const;

protected:
    template<typename T>
    void bind(Observable<T>& masterSignal, TokenSource<T>& slaveSignal);

    template<typename C>
    void sendCommand(std::function<void(std::shared_ptr<C>)> func);
    template<typename C, typename S1, typename T1>
    void sendCommand(std::function<void(std::shared_ptr<C>, std::shared_ptr<S1>)> func, T1 t1);
    template<typename C, typename S1, typename S2, typename T1, typename T2>
    void sendCommand(std::function<void(std::shared_ptr<C>, std::shared_ptr<S1>, std::shared_ptr<S2>)> func, T1 t1, T2 t2);
    template<typename C, typename R>
    void sendCommand(std::function<R(std::shared_ptr<C>)> func, std::function<void(R)> response);

private:
    std::weak_ptr<void> master;

    ProxyBridge& proxyBridge;

};

#include "data_proxy.tpp"
