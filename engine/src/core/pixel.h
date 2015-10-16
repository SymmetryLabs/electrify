#pragma once
#include "globals.h"

class Group;

/**
 * Pixels are individual lights that exist in 3D space on a structure;
 */
class Pixel {

public:
    Pixel(double x_ = 0, double y_ = 0, double z_ = 0);

    double x;
    double y;
    double z;

    shared_ptr<Group> parent;

};
