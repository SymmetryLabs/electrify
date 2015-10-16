#pragma once
#include "globals.h"

#include <cereal/types/memory.hpp>

#include "pixel.h"

template <typename Archive>
void serialize(Archive& archive, Pixel& pixel)
{
    archive(cereal::make_nvp("x", pixel.x),
        cereal::make_nvp("y", pixel.y),
        cereal::make_nvp("z", pixel.z),
        cereal::make_nvp("parent", pixel.parent));
}
