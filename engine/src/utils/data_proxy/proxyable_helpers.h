#pragma once

#include <memory>

#include "alloc_shared_ptr.h"

#define SYNTHESIZE_PROXYABLE(ProxyType) SYNTHESIZE_PROXYABLE_IMPL(ProxyType, override)
#define SYNTHESIZE_PROXYABLE_BASE(ProxyType) SYNTHESIZE_PROXYABLE_IMPL(ProxyType, )

#define SYNTHESIZE_PROXYABLE_IMPL(ProxyType, Override)                                      \
protected:                                                                                  \
virtual std::shared_ptr<void> makeAndCacheProxy(ProxyBridge& proxyBridge) Override          \
{                                                                                           \
    return allocSharedPtr<ProxyType>(                                                       \
        [this, &proxyBridge] (std::shared_ptr<ProxyType> proxy) {                           \
            this->cacheProxy(proxy, proxyBridge);                                           \
        }                                                                                   \
    , this->shared_from_this(this), proxyBridge);                                           \
}                                                                                           \
friend class ProxyType;
