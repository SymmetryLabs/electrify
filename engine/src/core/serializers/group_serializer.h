#pragma once
#include "globals.h"

#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include "group.h"

template <typename Archive>
void serialize(Archive& archive, Group& group)
{
    archive(cereal::make_nvp("x", group.x),
        cereal::make_nvp("y", group.y),
        cereal::make_nvp("z", group.z),
        cereal::make_nvp("rx", group.rx),
        cereal::make_nvp("ry", group.ry),
        cereal::make_nvp("rz", group.rz),
        cereal::make_nvp("name", group.name),
        cereal::make_nvp("parent", group.parent),
        cereal::make_nvp("members", group.members),
        cereal::make_nvp("pixels", group.pixels));
}
