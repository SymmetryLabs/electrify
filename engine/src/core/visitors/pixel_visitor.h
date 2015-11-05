#pragma once

#include "pixel.h"
#include "var_visitor.h"

template <typename Visitor, typename... PixelType,
    typename enable_if_all<int, are_same<Pixel, typename std::decay<PixelType>::type...>::value>::type = 0>
void performOnObjects(Visitor& visitor, PixelType&&... pixelObjects)
{
    visitor(pixelObjects.x...);
    visitor(pixelObjects.y...);
    visitor(pixelObjects.z...);
}
