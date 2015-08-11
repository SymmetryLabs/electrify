#include "square_wave.h"

float SquareWave::calculate(const FrameContext& frame) const
{
    return amplitude(frame) * floor(2 * frame.timeSeconds() * frequency(frame) + phase(frame));
}
