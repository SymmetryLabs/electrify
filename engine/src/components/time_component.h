#pragma once
#include "globals.h"

#include "basic_component.h"

class TimeComponent : public BasicComponent<float> {

public:

  float calculate(const FrameContext& frame) const override;

};
