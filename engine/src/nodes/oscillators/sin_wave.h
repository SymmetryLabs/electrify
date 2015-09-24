#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SinWave : public Waveform<Input> {

public:
    explicit SinWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};

#include "sin_wave.hpp"
