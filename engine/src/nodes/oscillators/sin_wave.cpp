#include "sin_wave.h"

SinWave::SinWave()
: Waveform("Sin wave")
{
}

float SinWave::calculate(const FrameContext& frame) const
{
    return amplitude(frame) * (sin(M_2_PI * frame.timeSeconds() * frequency(frame) + phase(frame)) + 1) / 2;
}
