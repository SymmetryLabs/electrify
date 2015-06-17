#pragma once
#include "constants.h"

struct FrameContext {

  FrameContext(const nanoseconds time_) : time(time_) {}
  virtual ~FrameContext() {}

  const nanoseconds time;

  const double timeSeconds() const {
    return duration_cast<duration<double>>(time).count();
  }

};
