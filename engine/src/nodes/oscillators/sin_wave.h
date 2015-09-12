#pragma once
#include "globals.h"

#include "waveform.h"

class SinWave : public Waveform {

public:
    explicit SinWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};
