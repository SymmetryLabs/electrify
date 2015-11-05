#include "object_owner.h"

ScopedPtr ObjectOwner::retain(const ScopedPtr& ptr)
{
    objects.push_back(ptr);
    return ptr;
}

ScopedPtr ObjectOwner::retainFork(const ScopedPtr& ptr)
{
    auto fork = ptr.fork();
    objects.push_back(fork);
    return fork;
}

void ObjectOwner::releaseAll()
{
    objects.clear();
}
