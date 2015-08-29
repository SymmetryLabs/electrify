#pragma once
#include "globals.h"

#include "waveform.h"

class SawWave : public Waveform {

public:
    SawWave();
    
    float calculate(const FrameContext& frame) const override;

};
