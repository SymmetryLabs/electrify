#include "perlin_noise_node.h"

PerlinNoiseNode::PerlinNoiseNode(NodeHandle& nodeHandle)
: BasicNode<float>(nodeHandle)
{
    nodeHandle.setName("Perlin noise");
    nodeHandle.registerInput("xInput", &xInput);
    nodeHandle.registerInput("yInput", &yInput);
    nodeHandle.registerInput("zInput", &zInput);
}

float PerlinNoiseNode::calculate(const FrameContext& frame) const
{
    return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
}
