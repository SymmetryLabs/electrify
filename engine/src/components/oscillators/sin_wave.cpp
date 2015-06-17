#include "sin_wave.h"

double SinWave::calculate(const FragmentContext& frag) const
{
  return amplitude(frag) * (sin(M_2_PI * frag.timeSeconds() * frequency(frag) + phase(frag)) + 1) / 2;
}
