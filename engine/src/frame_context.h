#pragma once
#include "globals.h"

#include "fragment_context.h"

struct FrameContext {

  FrameContext(const nanoseconds time_, const FragmentContext* frag_ = nullptr)
    : time(time_)
    , frag(frag_) {}
  FrameContext(const FrameContext& frame, const FragmentContext* frag_ = nullptr) 
    : time(frame.time)
    , frag(frag_) {}

  const nanoseconds time;
  const FragmentContext* const frag;

  double timeSeconds() const {
    return duration_cast<duration<double>>(time).count();
  }

};
