#pragma once
#include "constants.h"

/**
 * Groups collect one or more pixels together
 */
class Group {
  public:
    double x,y,z;
    double rx, ry, rz;
    Group(double _x = 0.0, double _y = 0.0, double _z = 0.0) {x = _x; y = _y; z = _z;}
    vector<Group> members;
};
