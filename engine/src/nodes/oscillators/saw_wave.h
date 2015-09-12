#pragma once
#include "globals.h"

#include "waveform.h"

class SawWave : public Waveform {

public:
    explicit SawWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};
