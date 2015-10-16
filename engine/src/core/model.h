#pragma once
#include "globals.h"

class Pixel;
class Group;

class Model {

public:
    vector<shared_ptr<Pixel>> pixels;
    shared_ptr<Group> root;

};
