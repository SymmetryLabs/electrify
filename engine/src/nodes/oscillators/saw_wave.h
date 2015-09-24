#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SawWave : public Waveform<Input> {

public:
    explicit SawWave(NodeHandle& nodeHandle);
    
    float calculate(const FrameContext& frame) const override;

};

#include "saw_wave.hpp"
