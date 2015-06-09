#pragma once
#include "constants.h"

#include "pixel.h"

class FragmentContext
{
  public:
    FragmentContext(shared_ptr<Pixel> pixel);
    virtual ~FragmentContext() {}

    shared_ptr<Pixel> pixel;
};
