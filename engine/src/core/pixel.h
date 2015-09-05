#pragma once
#include "globals.h"

/**
 * Pixels are individual lights that exist in 3D space on a structure;
 */
class Group;

class Pixel {

public:
    double x,y,z;
    Pixel(double _x = 0.0, double _y = 0.0, double _z = 0.0) {x = _x; y = _y; z = _z;}
    Group *parent = 0;

};
