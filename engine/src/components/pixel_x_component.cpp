#include "pixel_x_component.h"

float PixelXComponent::calculate(const FrameContext& frame) const
{
  return frame.frag->pixel.x;
}
