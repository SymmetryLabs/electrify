#include "scoped_ptr.h"

void ScopedPtr::release()
{
    if (container) {
        container->release();
        container = nullptr;
    }
}

ScopedPtr ScopedPtr::fork() const
{
    return ScopedPtr{container->ptr};
}

ScopedPtr::ScopedPtrContainer::ScopedPtrContainer(const std::shared_ptr<UniqueVoidPtr>& ptr_)
: ptr(ptr_)
{
}

ScopedPtr::ScopedPtrContainer::~ScopedPtrContainer()
{
    release();
}

void ScopedPtr::ScopedPtrContainer::release()
{
    ptr->reset();
    ptr = nullptr;
}

ScopedPtr::ScopedPtr(const std::shared_ptr<UniqueVoidPtr>& ptr)
: container{std::make_shared<ScopedPtrContainer>(ptr)}
{
}
