#include "square_wave.h"

SquareWave::SquareWave()
{
  registerOutput("value", &SquareWave::calculate_value);
}

double SquareWave::calculate_value(const FragmentContext& frag)
{
  return fmod(frag.time, 1.0) > 0.5? 1.0 : 0.0;
}
