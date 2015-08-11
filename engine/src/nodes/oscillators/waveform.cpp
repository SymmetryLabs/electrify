#include "waveform.h"

Waveform::Waveform()
{
    registerInput("amplitude", &amplitude, 1.0f);
    registerInput("frequency", &frequency, 1.0f);
    registerInput("phase", &phase);
}
