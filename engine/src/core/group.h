#pragma once
#include "globals.h"
#include "pixel.h"

/**
 * Groups collect one or more pixels together
 */
class Pixel;

class Group {
  public:
    double x,y,z;
    double rx, ry, rz;
    Group(double _x = 0.0, double _y = 0.0, double _z = 0.0) {x = _x; y = _y; z = _z;}
    vector<Group*> *members = new vector<Group*>();
    vector<Pixel*> *pixels = new vector<Pixel*>();
    string name;
    Group *parent = 0;
    string id;
};
