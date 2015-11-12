#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>

#include "observable_shared_ptr.h"
#include "forward_serialization.h"

FORWARD_SERIALIZATION_TEMPLATE(ObservableSharedPtr);

template <typename Archive, typename T>
void serialize(Archive& archive, ObservableSharedPtr<T>& osp)
{
    archive(osp.sp);
}
