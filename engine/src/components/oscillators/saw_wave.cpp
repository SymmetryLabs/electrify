#include "saw_wave.h"

double SawWave::calculate(const FragmentContext& frag) const
{
  double unused;
  return amplitude(frag) * modf(frag.timeSeconds() * frequency(frag) + phase(frag), &unused);
}
