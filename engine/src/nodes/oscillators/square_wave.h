#pragma once
#include "globals.h"

#include "waveform.h"

class SquareWave : public Waveform {

public:
    static const string nodeName() { return "Square wave"; }
    
    float calculate(const FrameContext& frame) const override;

};
