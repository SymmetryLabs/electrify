#include "time_component.h"

float TimeComponent::calculate(const FrameContext& frame) const
{
  return frame.timeSeconds();
}
