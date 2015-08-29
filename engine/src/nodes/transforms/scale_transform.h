#pragma once
#include "globals.h"

#include "scalar_transform.h"

class ScaleTransform : public ScalarTransform {

public:
    ScaleTransform();

    float calculate(const FrameContext& frame) const override;

    SignalFunction<float> multiplier;

};
