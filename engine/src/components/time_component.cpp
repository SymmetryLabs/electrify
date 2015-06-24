#include "time_component.h"

double TimeComponent::calculate(const FrameContext& frame) const
{
  return frame.timeSeconds();
}
