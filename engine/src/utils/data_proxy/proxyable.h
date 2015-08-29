#pragma once

#include <memory>
#include <unordered_map>

#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>

#include "virtual_enable_shared_from_this.h"
#include "data_proxy.h"

class ProxyableBase {

public:
    virtual ~ProxyableBase() {}

    template<typename ConcreteProxyType>
    std::shared_ptr<ConcreteProxyType> getProxy(ProxyBridge& proxyBridge);

protected:
    virtual std::shared_ptr<void> makeAndCacheProxy(ProxyBridge& proxyBridge) = 0;
    void cacheProxy(std::weak_ptr<void> proxy, ProxyBridge& proxyBridge);

private:
    std::unordered_map<boost::uuids::uuid, std::weak_ptr<void>, boost::hash<boost::uuids::uuid>> proxies;

};

class Proxyable : public virtual ProxyableBase, public virtual_enable_shared_from_this {

public:
    virtual ~Proxyable() {}

};

#define SYNTHESIZE_PROXYABLE(ProxyType)                                                     \
protected:                                                                                  \
virtual std::shared_ptr<void> makeAndCacheProxy(ProxyBridge& proxyBridge) override;         \
friend class ProxyType;

#define SYNTHESIZE_PROXYABLE_IMPL(MainType, ProxyType)                                      \
std::shared_ptr<void> MainType::makeAndCacheProxy(ProxyBridge& proxyBridge)                 \
{                                                                                           \
    auto proxy = std::make_shared<ProxyType>(this->shared_from_this(this), proxyBridge);    \
    cacheProxy(proxy, proxyBridge);                                                         \
    proxy->init(this->shared_from_this(this), proxyBridge);                                 \
    return proxy;                                                                           \
}                                                                                           \

#include "proxyable.tpp"
