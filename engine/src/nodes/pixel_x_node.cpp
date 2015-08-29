#include "pixel_x_node.h"

PixelXNode::PixelXNode()
: BasicNode<float>("Pixel.x")
{
}

float PixelXNode::calculate(const FrameContext& frame) const
{
    return frame.frag->pixel.x;
}
