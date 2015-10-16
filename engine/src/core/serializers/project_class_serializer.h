#pragma once
#include "globals.h"

#include <cereal/types/memory.hpp>

#include "project.h"
#include "model_serializer.h"

template <typename Archive>
void serialize(Archive& archive, Project& project)
{
    archive(cereal::make_nvp("model", project.model));
}
