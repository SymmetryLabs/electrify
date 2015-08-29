#include "waveform.h"

Waveform::Waveform(const string& name)
: BasicNode<float>(name)
{
    registerInput("amplitude", &amplitude, 1.0f);
    registerInput("frequency", &frequency, 1.0f);
    registerInput("phase", &phase);
}
