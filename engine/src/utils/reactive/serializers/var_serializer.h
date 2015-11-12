#pragma once

#include <cereal/archives/json.hpp>

#include "var.h"
#include "forward_serialization.h"

FORWARD_SERIALIZATION_TEMPLATE(Var);

template <typename Archive, typename T>
void save(Archive& archive, const Var<T>& v)
{
    archive(v.getValue());
}

template <typename Archive, typename T>
void load(Archive& archive, Var<T>& v)
{
    T t;
    archive(t);
    v.emit(std::move(t));
}
