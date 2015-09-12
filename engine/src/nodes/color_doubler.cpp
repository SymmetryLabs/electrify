#include "color_doubler.h"

ColorDoubler::ColorDoubler(NodeHandle& nodeHandle)
: BasicNode<Color>(nodeHandle)
{
    nodeHandle.setName("Color doubler");
    nodeHandle.registerInput("color", &colorInput);
}

Color ColorDoubler::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() * 2);
    return in;
}
