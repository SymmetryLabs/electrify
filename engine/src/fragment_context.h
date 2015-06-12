#pragma once
#include "constants.h"

#include "pixel.h"

class FragmentContext {

public:
  FragmentContext(const Pixel &pixel_) : pixel(pixel_) {}
  virtual ~FragmentContext() {}

  const Pixel& pixel;
  double time = 0;

};
