#pragma once
#include "globals.h"

// class Group;

/**
 * Pixels are individual lights that exist in 3D space on a structure;
 */
class Pixel {

public:
    Pixel();
    Pixel(double x, double y, double z);

    Var<double> x;
    Var<double> y;
    Var<double> z;

    // shared_ptr<Group> parent;

    template <typename Visitor, typename... PixelType,
        typename enable_if_all<int, are_same<Pixel, typename std::decay<PixelType>::type...>::value>::type>
    void performOnObjects(Visitor& visitor, PixelType&&... pixelObjects);

};
