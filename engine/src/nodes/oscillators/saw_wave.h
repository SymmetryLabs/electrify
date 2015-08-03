#pragma once
#include "globals.h"

#include "waveform.h"

class SawWave : public Waveform {

public:
  static const string nodeName() { return "Sawtooth wave"; }
  
  float calculate(const FrameContext& frame) const override;

};
