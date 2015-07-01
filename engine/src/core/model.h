#pragma once
#include "globals.h"

#include "group.h"
#include "pixel.h"

class Model {

public:
  vector<Pixel*> pixels;
  Group *root;

};
