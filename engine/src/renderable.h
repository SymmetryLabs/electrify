#pragma once
#include "globals.h"

#include "model.h"
#include "frame_context.h"
#include "color.h"

class Renderable {

public:
  virtual ~Renderable() {}

  virtual void initRenderable(__attribute__((unused)) const Model& model) {}
  virtual void deinitRenderable() {}

  virtual void updateRenderable(__attribute__((unused)) const FrameContext& frame) {}
  virtual void renderRenderable(__attribute__((unused)) const FrameContext& frame,
                                __attribute__((unused)) vector<Color>& colorBuffer) {}

};
