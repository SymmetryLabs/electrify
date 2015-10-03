#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>

#include "observable_map.h"
#include "forward_serialization.h"

FORWARD_SERIALIZATION_TEMPLATE_2(ObservableMap);

template<typename Archive, typename KeyT, typename ValueT>
void serialize(Archive& archive, ObservableMap<KeyT, ValueT>& om)
{
    archive(om.m);
}
