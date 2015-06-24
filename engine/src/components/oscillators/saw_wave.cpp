#include "saw_wave.h"

double SawWave::calculate(const FrameContext& frame) const
{
  double unused;
  return amplitude(frame) * modf(frame.timeSeconds() * frequency(frame) + phase(frame), &unused);
}
