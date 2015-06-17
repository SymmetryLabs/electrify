#include "hsv_component.h"

HsvComponent::HsvComponent()
{
  registerInput("hue", &hue);
  registerInput("saturation", &saturation, 1.0);
  registerInput("value", &value, 1.0);
}

Color HsvComponent::calculate(const FragmentContext& frag) const
{
  Color in;
  in.fromHSV(hue(frag), saturation(frag), value(frag));
  return in;
}
