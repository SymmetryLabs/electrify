#pragma once
#include "globals.h"

#include "waveform.h"

class SquareWave : public Waveform {

public:
  double calculate(const FrameContext& frame) const override;

};
