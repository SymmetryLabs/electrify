#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/boost_variant.hpp>

#include "data_storage.h"
#include "forward_serialization.h"

FORWARD_SERIALIZATION(DataStorage);

template <typename Archive>
void serialize(Archive& archive, DataStorage& ds)
{
    archive(ds.storage);
}
