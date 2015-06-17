#pragma once
#include "constants.h"

#include "waveform.h"

class SquareWave : public Waveform {

public:
  double calculate(const FragmentContext& frag) const override;

};
