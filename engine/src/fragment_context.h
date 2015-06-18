#pragma once
#include "globals.h"

#include "pixel.h"
#include "frame_context.h"

struct FragmentContext : public FrameContext {

  FragmentContext(const Pixel& pixel_, const FrameContext& frame) : FrameContext(frame), pixel(pixel_) {}
  virtual ~FragmentContext() {}

  const Pixel& pixel;

};
