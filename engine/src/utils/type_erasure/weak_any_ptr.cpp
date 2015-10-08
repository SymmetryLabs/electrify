#include "weak_any_ptr.h"

bool WeakAnyPtr::expired() const
{
    return weakPtr.expired();
}

SharedAnyPtr WeakAnyPtr::lock() const
{
    return SharedAnyPtr(weakPtr.lock(), anyPtr);
}

void WeakAnyPtr::reset()
{
    anyPtr.reset();
    weakPtr.reset();
}

WeakAnyPtr& WeakAnyPtr::swap(WeakAnyPtr& other)
{
    anyPtr.swap(other.anyPtr);
    weakPtr.swap(other.weakPtr);
    return *this;
}

SharedAnyPtr::operator bool() const
{
    return static_cast<bool>(anyPtr);
}

SharedAnyPtr::SharedAnyPtr(const std::shared_ptr<void>& sharedPtr_, const AnyPtr& anyPtr_)
: sharedPtr(sharedPtr_)
, anyPtr(anyPtr_)
{
}
