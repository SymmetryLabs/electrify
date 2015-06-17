#include "sawtooth_wave.h"

double SawtoothWave::calculate(const FragmentContext& frag) const
{
  double unused;
  return amplitude(frag) * modf(frag.timeSeconds() * frequency(frag) + phase(frag), &unused);
}
