template<typename ConcreteProxyType>
std::shared_ptr<ConcreteProxyType> ProxyableBase::getProxy(ProxyBridge& proxyBridge)
{
    std::shared_ptr<void> proxy;
    auto iter = proxies.find(proxyBridge.uuid);
    if (iter != proxies.end()) {
        proxy = iter->second.lock();
    }
    if (!proxy) {
        proxy = makeAndCacheProxy(proxyBridge);
    }
    return std::static_pointer_cast<ConcreteProxyType>(proxy);
}
