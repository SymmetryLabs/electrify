#pragma once

#include <memory>

#include "any_ptr.h"

class SharedAnyPtr;

// Similar to std::weak_ptr<void>, except the original type
// can be retrieved in a polymorphic fashion.
//
// Requires all classes in the hierarchy to implement one of the
// ENABLE_TYPE_ERASURE_* macros
class WeakAnyPtr {

public:
    WeakAnyPtr() = default;

    template <typename ValueType>
    WeakAnyPtr(const std::shared_ptr<ValueType>& value);

    bool expired() const;

    template <typename T>
    std::shared_ptr<T> get() const;

    SharedAnyPtr lock() const;

    void reset();
    WeakAnyPtr& swap(WeakAnyPtr& other);

private:
    std::weak_ptr<void> weakPtr;
    AnyPtr anyPtr;

};

class SharedAnyPtr {

public:
    SharedAnyPtr() = default;

    template <typename T>
    std::shared_ptr<T> get() const;

    explicit operator bool() const;

private:
    SharedAnyPtr(const std::shared_ptr<void>& sharedPtr, const AnyPtr& anyPtr);

    std::shared_ptr<void> sharedPtr;
    AnyPtr anyPtr;

    friend class WeakAnyPtr;
};

#include "weak_any_ptr.hpp"
