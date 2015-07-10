#pragma once
#include "globals.h"

#include "waveform.h"

class SinWave : public Waveform {

public:
  static const string componentName() { return "Sin wave"; }
  
  float calculate(const FrameContext& frame) const override;

};
