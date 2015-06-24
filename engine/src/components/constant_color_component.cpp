#include "constant_color_component.h"

Color ConstantColorComponent::calculate(__attribute__((unused)) const FrameContext& frame) const
{
  return Color(0xFFFF0000);
}
