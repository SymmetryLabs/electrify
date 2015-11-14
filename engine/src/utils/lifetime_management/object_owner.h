#pragma once

#include <vector>

#include "scoped_ptr.h"

class ObjectOwner {

public:
    virtual ~ObjectOwner() = default;

    template <typename T>
    ScopedPtr retain(std::unique_ptr<T>&& ptr);

    ScopedPtr retain(const ScopedPtr& ptr);
    ScopedPtr retainFork(const ScopedPtr& ptr);

    void clear();
    void releaseAll();

private:
    std::vector<ScopedPtr> objectPtrs;

};

#include "object_owner.hpp"
