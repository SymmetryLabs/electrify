#include "square_wave.h"

double SquareWave::calculate(const FragmentContext& frag) const
{
  return amplitude(frag) * floor(2 * frag.timeSeconds() * frequency(frag) + phase(frag));
}
