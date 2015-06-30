#include "translate_component.h"

TranslateComponent::TranslateComponent()
{
  registerInput("translateX", &translateX);
  registerInput("translateY", &translateY);
  registerInput("translateZ", &translateZ);
}

FrameContext TranslateComponent::modifyContext(const FrameContext& original)
{
  Pixel pixel {original.frag->pixel};
  pixel.x += translateX(original);
  pixel.y += translateY(original);
  pixel.z += translateZ(original);
  
  FragmentContext frag(pixel);
  FrameContext childFrame(original, &frag);
  return childFrame;
}
