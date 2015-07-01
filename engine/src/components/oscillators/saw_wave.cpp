#include "saw_wave.h"

float SawWave::calculate(const FrameContext& frame) const
{
  float unused;
  return amplitude(frame) * modf(frame.timeSeconds() * frequency(frame) + phase(frame), &unused);
}
