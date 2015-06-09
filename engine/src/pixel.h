#pragma once
#include "constants.h"

/**
 * Pixels are individual lights that exist in 3D space on a structure;
 */
class Pixel {
public:
  double x,y,z;
  void* meta; // TODO this needs a type

};


