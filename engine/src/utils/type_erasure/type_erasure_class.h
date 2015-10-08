#pragma once

class TypeErasure {

public:
    virtual ~TypeErasure() = default;

    template <typename T>
    T* get() const;

protected:
    virtual void raise() const = 0;

};

template <typename T>
std::shared_ptr<TypeErasure> eraseType(T& t);

#include "type_erasure_class.hpp"
