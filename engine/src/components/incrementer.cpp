#include "incrementer.h"

Incrementer::Incrementer()
{
  registerInput("color", &colorInput);
  registerOutput("color", &Incrementer::incrementColor);
}

void Incrementer::init()
{
  increment = 0;
}

void Incrementer::update(const FrameContext& frame)
{
  increment = (increment + 0x100) % 0x10000;
}

Color Incrementer::incrementColor(const FragmentContext& frag)
{
  Color in = colorInput->calculate(frag);
  in.fromRGBA(in.asRGBA() + increment);
  return in;
}
