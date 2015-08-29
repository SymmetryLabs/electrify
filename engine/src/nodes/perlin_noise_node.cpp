#include "perlin_noise_node.h"

PerlinNoiseNode::PerlinNoiseNode()
: BasicNode<float>("Perlin noise")
{
    registerInput("xInput", &xInput);
    registerInput("yInput", &yInput);
    registerInput("zInput", &zInput);
}

float PerlinNoiseNode::calculate(const FrameContext& frame) const
{
    return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
}
