#include "proxyable.h"

void ProxyableBase::cacheProxy(std::weak_ptr<void> proxy, ProxyBridge& proxyBridge)
{
    proxies[proxyBridge.uuid] = proxy;
}