#include "any_ptr.h"

AnyPtr::operator bool() const
{
    return static_cast<bool>(typeErasure);
}

bool AnyPtr::operator!() const
{
    return !typeErasure;
}

bool AnyPtr::empty() const
{
    return !typeErasure;
}

void AnyPtr::reset()
{
    typeErasure.reset();
}

AnyPtr& AnyPtr::swap(AnyPtr& other)
{
    typeErasure.swap(other.typeErasure);
    return *this;
}
