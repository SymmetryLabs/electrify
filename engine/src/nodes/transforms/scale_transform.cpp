#include "scale_transform.h"

ScaleTransform::ScaleTransform(NodeHandle& nodeHandle)
: ScalarTransform(nodeHandle)
{
    nodeHandle.setName("Scale");
    nodeHandle.registerInput("multiplier", &multiplier, 1.0f);
}

float ScaleTransform::calculate(const FrameContext& frame) const
{
    return multiplier(frame) * input(frame);
}
