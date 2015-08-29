#include "data_proxy.h"

DataProxy::DataProxy(std::weak_ptr<void> master, ProxyBridge& proxyBridge)
: master(master)
, proxyBridge(proxyBridge)
{
}

std::weak_ptr<void> DataProxy::getMaster() const
{
    return master;
}
