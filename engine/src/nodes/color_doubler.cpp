#include "color_doubler.h"

ColorDoubler::ColorDoubler()
{
    registerInput("color", &colorInput);
}

Color ColorDoubler::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() * 2);
    return in;
}
