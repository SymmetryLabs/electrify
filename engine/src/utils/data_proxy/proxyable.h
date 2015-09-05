#pragma once

#include <memory>
#include <unordered_map>

#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>

#include "virtual_enable_shared_from_this.h"
#include "data_proxy.h"
#include "proxyable_helpers.h"

class Proxyable : public virtual_enable_shared_from_this_base {

public:
    virtual ~Proxyable() = default;

    template<typename ConcreteProxyType>
    std::shared_ptr<ConcreteProxyType> getProxy(ProxyBridge& proxyBridge);

protected:
    void cacheProxy(std::weak_ptr<void> proxy, ProxyBridge& proxyBridge);

private:
    std::unordered_map<boost::uuids::uuid, std::weak_ptr<void>, boost::hash<boost::uuids::uuid>> proxies;

    SYNTHESIZE_PROXYABLE_BASE(DataProxy)

};

#include "proxyable.tpp"
