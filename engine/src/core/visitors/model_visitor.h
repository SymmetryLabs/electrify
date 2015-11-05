#pragma once

#include "model.h"
#include "observable_vector_visitor.h"
#include "pixel_visitor.h"

template <typename Visitor, typename... ModelType,
    typename enable_if_all<int, are_same<Model, typename std::decay<ModelType>::type...>::value>::type = 0>
void performOnObjects(Visitor& visitor, ModelType&&... modelObjects)
{
    visitor(modelObjects.pixels...);
    // visitor(modelObjects.root...);
}
