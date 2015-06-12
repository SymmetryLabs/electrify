#include "incrementer.h"

Incrementer::Incrementer()
  :colorSocket(new Socket<Color>())
{
  registerInput("color", unique_ptr<BaseSocket>(colorSocket));
  registerOutput("color", &Incrementer::increment_color);
}

Color Incrementer::increment_color(const FragmentContext& frag)
{
  Color in = colorSocket->calculate(frag);
  in.fromRGBA(in.asRGBA() + _increment);
  return in;
}

void Incrementer::update(const FrameContext& frame)
{
	_increment++;
}
