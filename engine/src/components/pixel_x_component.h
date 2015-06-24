#pragma once
#include "globals.h"

#include "basic_component.h"

class PixelXComponent : public BasicComponent<double> {

public:

  double calculate(const FrameContext& frame) const override;

};
