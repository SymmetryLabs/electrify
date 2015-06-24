#pragma once
#include "globals.h"

#include "pixel.h"

struct FragmentContext {

  FragmentContext(const Pixel& pixel_) : pixel(pixel_) {}

  const Pixel& pixel;

};
