#pragma once
#include "globals.h"

#include "pixel.h"

struct FragmentContext {

  FragmentContext(const Pixel& pixel_) : pixel(pixel_) {}

  const Pixel& pixel;

  // const vec3 pt3;
  // const vec2 pt2;

};
