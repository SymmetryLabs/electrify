#include "waveform.h"

Waveform::Waveform(NodeHandle& nodeHandle)
: BasicNode<float>(nodeHandle)
{
    nodeHandle.registerInput("amplitude", &amplitude, 1.0f);
    nodeHandle.registerInput("frequency", &frequency, 1.0f);
    nodeHandle.registerInput("phase", &phase);
}
