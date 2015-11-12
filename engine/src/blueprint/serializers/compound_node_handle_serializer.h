#pragma once
#include "globals.h"

#include <cereal/cereal.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include "compound_node.h"

#include "node_handle_serializer.h"
#include "observable_vector_serializer.h"
#include "node_wire_serializer.h"

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(CompoundNodeHandle, cereal::specialization::non_member_serialize);

template <typename Archive>
void serialize(Archive& archive, CompoundNodeHandle& handle)
{
    archive(
        cereal::make_nvp("NodeHandle", cereal::base_class<NodeHandle>(&handle)),
        cereal::make_nvp("subnodes", handle.subnodes),
        cereal::make_nvp("nodeWires", handle.nodeWires)
    );
}
