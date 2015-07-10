#pragma once
#include "globals.h"

#include "basic_component.h"

class TimeComponent : public BasicComponent<float> {

public:
  static const string componentName() { return "Time"; }

  float calculate(const FrameContext& frame) const override;

};
