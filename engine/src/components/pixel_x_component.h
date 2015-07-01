#pragma once
#include "globals.h"

#include "basic_component.h"

class PixelXComponent : public BasicComponent<float> {

public:

  float calculate(const FrameContext& frame) const override;

};
