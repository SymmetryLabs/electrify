#pragma once
#include "globals.h"

#include "model.h"
#include "frame_context.h"
#include "color.h"

class Renderable {

public:
  virtual ~Renderable() {}

  virtual void initRenderable(const Model&) {}
  virtual void deinitRenderable() {}

  virtual void updateRenderable(const FrameContext&) {}
  virtual void renderRenderable(const FrameContext&, vector<Color>&) {}

};
