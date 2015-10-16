#pragma once
#include "globals.h"

#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

#include "model.h"
#include "pixel_serializer.h"
#include "group_serializer.h"

template <typename Archive>
void serialize(Archive& archive, Model& model)
{
    archive(cereal::make_nvp("pixels", model.pixels),
        cereal::make_nvp("root", model.root));
}
