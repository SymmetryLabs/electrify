#include "color_doubler.h"

ColorDoubler::ColorDoubler()
{
  registerInput("color", &colorInput);
  registerOutput("color", &ColorDoubler::doubleColor);
}

Color ColorDoubler::doubleColor(const FragmentContext& frag)
{
  Color in = colorInput->calculate(frag);
  in.fromRGBA(in.asRGBA() * 2);
  return in;
}
