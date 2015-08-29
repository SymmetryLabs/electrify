#include "color_doubler.h"

ColorDoubler::ColorDoubler()
: BasicNode<Color>("Color doubler")
{
    registerInput("color", &colorInput);
}

Color ColorDoubler::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() * 2);
    return in;
}
