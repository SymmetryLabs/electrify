#include "proxyable.h"

void Proxyable::cacheProxy(std::weak_ptr<void> proxy, ProxyBridge& proxyBridge)
{
    proxies[proxyBridge.uuid] = proxy;
}