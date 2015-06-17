#include "constant_color_component.h"

Color ConstantColorComponent::calculate(__attribute__((unused)) const FragmentContext& frag) const
{
  return Color(0xFFFF0000);
}
