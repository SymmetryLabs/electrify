#pragma once

#include <memory>

#include "type_erasure_class.h"

// Similar to void*, except the original type can be retrieved
// in a polymorphic fashion.
//
// Requires all classes in the hierarchy to implement one of the
// ENABLE_TYPE_ERASURE_* macros
class AnyPtr {

public:
    AnyPtr() = default;

    template <typename ValueType>
    AnyPtr(ValueType& value);

    template <typename T>
    T* get() const;

    explicit operator bool() const;
    bool operator!() const;

    bool empty() const;

    void reset();
    AnyPtr& swap(AnyPtr& other);

private:

    void raiseException() const;

    std::shared_ptr<TypeErasure> typeErasure;

};

#include "any_ptr.hpp"
