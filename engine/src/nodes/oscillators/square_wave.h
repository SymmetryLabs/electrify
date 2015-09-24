#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SquareWave : public Waveform<Input> {

public:
    explicit SquareWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};

#include "square_wave.hpp"
