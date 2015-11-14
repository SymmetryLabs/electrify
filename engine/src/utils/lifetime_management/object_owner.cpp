#include "object_owner.h"

ScopedPtr ObjectOwner::retain(const ScopedPtr& ptr)
{
    objectPtrs.push_back(ptr);
    return ptr;
}

ScopedPtr ObjectOwner::retainFork(const ScopedPtr& ptr)
{
    auto fork = ptr.fork();
    objectPtrs.push_back(fork);
    return fork;
}

void ObjectOwner::clear()
{
    objectPtrs.clear();
}

void ObjectOwner::releaseAll()
{
    for (auto ptr : objectPtrs) {
        ptr.release();
    }
    objectPtrs.clear();
}
