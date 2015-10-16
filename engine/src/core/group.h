#pragma once
#include "globals.h"

#include "pixel.h"

/**
 * Groups collect one or more pixels together
 */
class Group {

public:
    Group(double x_ = 0, double y_ = 0, double z_ = 0);

    double x;
    double y;
    double z;

    double rx = 0;
    double ry = 0;
    double rz = 0;

    string name;
    shared_ptr<Group> parent;

    vector<shared_ptr<Group>> members;
    vector<shared_ptr<Pixel>> pixels;

};
