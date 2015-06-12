#include "constant_color_component.h"

ConstantColorComponent::ConstantColorComponent()
{
  registerOutput("color", &ConstantColorComponent::calculate_color);
}

Color ConstantColorComponent::calculate_color(__attribute__((unused)) const FragmentContext& frag)
{
  return Color(255);
};
