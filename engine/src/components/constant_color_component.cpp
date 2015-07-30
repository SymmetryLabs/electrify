#include "constant_color_component.h"

Color ConstantColorComponent::calculate(const FrameContext&) const
{
  return color;
}
