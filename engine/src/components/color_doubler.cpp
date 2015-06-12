#include "color_doubler.h"

ColorDoubler::ColorDoubler()
  :colorSocket(new Socket<Color>())
{
  registerInput("color", unique_ptr<BaseSocket>(colorSocket));
  registerOutput("color", &ColorDoubler::double_color);
}

Color ColorDoubler::double_color(const FragmentContext& frag)
{
  Color in = colorSocket->calculate(frag);
  in.fromRGBA(in.asRGBA() * 2);
  return in;
}
