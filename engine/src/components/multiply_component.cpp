#include "multiply_component.h"

MultiplyComponent::MultiplyComponent()
{
  registerInput("signalInput", &signalInput);
  registerInput("multiplyAmount", &multiplyAmount);
}

double MultiplyComponent::calculate(const FrameContext& frame) const
{
  return signalInput(frame) * multiplyAmount(frame);
}
