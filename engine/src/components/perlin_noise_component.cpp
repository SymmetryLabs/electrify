#include "perlin_noise_component.h"

PerlinNoiseComponent::PerlinNoiseComponent()
{
  registerInput("xInput", &xInput);
  registerInput("yInput", &yInput);
  registerInput("zInput", &zInput);
}

double PerlinNoiseComponent::calculate(const FrameContext& frame) const
{
  return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
}
