#pragma once
#include "globals.h"

class Pixel;
class Group;

class Model {

public:
    vector<Pixel*> pixels;
    Group* root;

};
