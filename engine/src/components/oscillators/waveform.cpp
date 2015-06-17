#include "waveform.h"

Waveform::Waveform()
{
  registerInput("amplitude", &amplitude, 1.0);
  registerInput("frequency", &frequency, 1.0);
  registerInput("phase", &phase);
}
