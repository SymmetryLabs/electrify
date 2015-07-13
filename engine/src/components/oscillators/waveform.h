#pragma once
#include "globals.h"

#include "basic_component.h"

class Waveform : public BasicComponent<float> {

public:
  Waveform();
  virtual ~Waveform() {}

  SignalFunction<float> amplitude;
  SignalFunction<float> frequency;
  SignalFunction<float> phase;

};
