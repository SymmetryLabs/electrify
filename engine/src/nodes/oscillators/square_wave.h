#pragma once
#include "globals.h"

#include "waveform.h"

class SquareWave : public Waveform {

public:
    explicit SquareWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};
