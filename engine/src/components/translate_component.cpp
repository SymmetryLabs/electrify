#include "translate_component.h"

TranslateComponent::TranslateComponent()
{
  registerInput("translateX", &translateX);
  registerInput("translateY", &translateY);
  registerInput("translateZ", &translateZ);
}

void* TranslateComponent::calculate(const FrameContext& frame) const
{
  Pixel pixel {frame.frag->pixel};
  pixel.x += translateX(frame);
  pixel.y += translateY(frame);
  pixel.z += translateZ(frame);
  
  FragmentContext frag(pixel);
  FrameContext childFrame(frame, &frag);
  return signalInput(childFrame);
}
