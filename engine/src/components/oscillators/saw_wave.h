#pragma once
#include "globals.h"

#include "waveform.h"

class SawWave : public Waveform {

public:
  double calculate(const FrameContext& frame) const override;

};
