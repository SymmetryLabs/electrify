#pragma once
#include "globals.h"

#include "waveform.h"

class SquareWave : public Waveform {

public:
    SquareWave();
    
    float calculate(const FrameContext& frame) const override;

};
