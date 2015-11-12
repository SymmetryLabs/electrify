#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "observable_vector.h"
#include "forward_serialization.h"

FORWARD_SERIALIZATION_TEMPLATE(ObservableVector);

template <typename Archive, typename T>
void serialize(Archive& archive, ObservableVector<T>& ov)
{
    archive(ov.v);
}
