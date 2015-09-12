#include "saw_wave.h"

SawWave::SawWave(NodeHandle& nodeHandle)
: Waveform(nodeHandle)
{
    nodeHandle.setName("Sawtooth wave");
}

float SawWave::calculate(const FrameContext& frame) const
{
    float unused;
    return amplitude(frame) * modf(frame.timeSeconds() * frequency(frame) + phase(frame), &unused);
}
