#include "scale_transform.h"

ScaleTransform::ScaleTransform()
: ScalarTransform("Scale")
{
    registerInput("multiplier", &multiplier, 1.0f);
}

float ScaleTransform::calculate(const FrameContext& frame) const
{
    return multiplier(frame) * input(frame);
}
