#pragma once
#include "globals.h"

#include "basic_component.h"

class TimeComponent : public BasicComponent<double> {

public:

  double calculate(const FrameContext& frame) const override;

};
