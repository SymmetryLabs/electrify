#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SinWave : public Waveform<Input> {

public:
    static void configure(SinWave<Input>& node, NodeHandle& handle);
    
    float calculate(const FrameContext& frame) const override;

};

#include "sin_wave.hpp"
