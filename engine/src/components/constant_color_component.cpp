#include "constant_color_component.h"

ConstantColorComponent::ConstantColorComponent()
{
  registerOutput("color", &ConstantColorComponent::calculateColor);
}

Color ConstantColorComponent::calculateColor(__attribute__((unused)) const FragmentContext& frag)
{
  return Color(0xFFFF0000);
}
