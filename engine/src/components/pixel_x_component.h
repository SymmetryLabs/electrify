#pragma once
#include "globals.h"

#include "basic_component.h"

class PixelXComponent : public BasicComponent<float> {

public:
  static const string componentName() { return "Pixel.x"; }

  float calculate(const FrameContext& frame) const override;

};
