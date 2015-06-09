#pragma once
#include "constants.h"

class FrameContext
{
  public:
    Pixel *pixel;
    Group *topLevel;
    double time = 0;
};