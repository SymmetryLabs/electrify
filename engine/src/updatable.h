#pragma once
#include "constants.h"

#include "frame_context.h"

class Updatable {

public:
  Updatable() {}
  virtual ~Updatable() {}

  virtual void init() {}

  /**
   * Tells the component to update its model according to the current time
   */
  virtual void update(const FrameContext& f) {}

};
