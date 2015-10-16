#pragma once

#include <memory>

/*
 * this class allows unique_ptr to be captured by lambdas
 */
template <typename T>
class ReleasableSharedPtr {

public:
    explicit ReleasableSharedPtr(std::unique_ptr<T>&& inPtr);

    std::unique_ptr<T> release() const;

private:
    std::shared_ptr<bool> released;
    std::shared_ptr<T> ptr;

};

#include "releasable_shared_ptr.hpp"
