#include "pixel_x_component.h"

double PixelXComponent::calculate(const FrameContext& frame) const
{
  return frame.frag->pixel.x;
}