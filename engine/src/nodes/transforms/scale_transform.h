#pragma once
#include "globals.h"

#include "scalar_transform.h"

class ScaleTransform : public ScalarTransform {

public:
    explicit ScaleTransform(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

    SignalFunction<float> multiplier;

};
