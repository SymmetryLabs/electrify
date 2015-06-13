#include "square_wave.h"

SquareWave::SquareWave()
{
  registerOutput("value", &SquareWave::calculateValue);
}

double SquareWave::calculateValue(const FragmentContext& frag)
{
  return fmod(frag.time, 1.0) > 0.5? 1.0 : 0.0;
}
