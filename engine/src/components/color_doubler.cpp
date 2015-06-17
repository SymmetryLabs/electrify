#include "color_doubler.h"

ColorDoubler::ColorDoubler()
{
  registerInput("color", &colorInput);
}

Color ColorDoubler::calculate(const FragmentContext& frag) const
{
  Color in = colorInput(frag);
  in.fromRGBA(in.asRGBA() * 2);
  return in;
}
