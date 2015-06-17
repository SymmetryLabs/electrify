#pragma once
#include "constants.h"

#include "basic_component.h"

class Waveform : public BasicComponent<double> {

public:
  Waveform();
  virtual ~Waveform() {}

  SignalFunction<double> amplitude;
  SignalFunction<double> frequency;
  SignalFunction<double> phase;

};
