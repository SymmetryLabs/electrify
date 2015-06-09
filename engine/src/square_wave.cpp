#include "square_wave.h"

#include <math.h>
#include "frame_context.h"

SquareWave::SquareWave()
{
  string valueOutputName("value");
  Signal<double>* doubleSignal =  new Signal<double>();
  doubleSignal->calculate_function = [this]
    (FrameContext f)
    {
      return this->calculate_value(f);
    };
  addOutput<double>(valueOutputName, doubleSignal);
}

double SquareWave::calculate_value(FrameContext f)
{
  _value = fmod(f.time, 1.0) > 0.5? 1.0 : 0.0;
  return _value;
}
