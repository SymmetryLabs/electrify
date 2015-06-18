#pragma once
#include "globals.h"

struct FrameContext {

  FrameContext(const nanoseconds time_) : time(time_) {}
  virtual ~FrameContext() {}

  const nanoseconds time;

  double timeSeconds() const {
    return duration_cast<duration<double>>(time).count();
  }

};
