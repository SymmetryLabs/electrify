#pragma once
#include "globals.h"

#include "component.h"
#include "frame_context.h"

template <typename V>
class BasicComponent : public Component {

public:
  BasicComponent();
  virtual ~BasicComponent() {}

  virtual V calculate(const FrameContext& frame) const = 0;

};

#include "basic_component.tpp"
