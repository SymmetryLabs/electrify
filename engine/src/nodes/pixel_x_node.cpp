#include "pixel_x_node.h"

float PixelXNode::calculate(const FrameContext& frame) const
{
    return frame.frag->pixel.x;
}
