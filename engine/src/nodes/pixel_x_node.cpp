#include "pixel_x_node.h"

PixelXNode::PixelXNode(NodeHandle& nodeHandle)
: BasicNode<float>(nodeHandle)
{
    nodeHandle.setName("Pixel.x");
}

float PixelXNode::calculate(const FrameContext& frame) const
{
    return frame.frag->pixel.x;
}
