#pragma once
#include "globals.h"

#include <cereal/cereal.hpp>
#include <cereal/types/base_class.hpp>

#include "blueprint.h"

#include "compound_node_handle_serializer.h"

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(Blueprint, cereal::specialization::non_member_serialize);

template <typename Archive>
void serialize(Archive& archive, Blueprint& blueprint)
{
    archive(
        cereal::make_nvp("CompoundNodeHandle", cereal::base_class<CompoundNodeHandle>(&blueprint))
    );
}
