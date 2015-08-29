#pragma once
#include "globals.h"

#include "waveform.h"

class SinWave : public Waveform {

public:
    SinWave();
    
    float calculate(const FrameContext& frame) const override;

};
