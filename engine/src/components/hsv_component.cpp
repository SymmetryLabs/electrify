#include "hsv_component.h"

HsvComponent::HsvComponent()
{
  registerInput("hue", &hue);
  registerInput("saturation", &saturation, 1.0f);
  registerInput("value", &value, 1.0f);
}

Color HsvComponent::calculate(const FrameContext& frame) const
{
  Color in;
  in.fromHSV(hue(frame), saturation(frame), value(frame));
  return in;
}
