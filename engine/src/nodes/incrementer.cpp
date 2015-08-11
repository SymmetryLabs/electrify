#include "incrementer.h"

Incrementer::Incrementer()
{
    registerInput("color", &colorInput);
}

void Incrementer::init()
{
    increment = 0;
}

void Incrementer::update(const FrameContext& frame)
{
    increment = (increment + 0x100) % 0x10000;
}

Color Incrementer::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() + increment);
    return in;
}
