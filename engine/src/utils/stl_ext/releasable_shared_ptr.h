#pragma once

#include <memory>

/*
 * this class allows unique_ptr to be captured by lambdas
 */
template <typename T>
class ReleasableSharedPtr {

public:
    typedef typename std::shared_ptr<T>::element_type element_type;

    explicit ReleasableSharedPtr(std::unique_ptr<T>&& inPtr);

    std::unique_ptr<T> release() const;

    element_type& operator*() const noexcept { return ptr.operator*(); }

    explicit operator bool() const noexcept { return !*released; }

private:
    std::shared_ptr<bool> released;
    std::shared_ptr<T> ptr;

};

#include "releasable_shared_ptr.hpp"
