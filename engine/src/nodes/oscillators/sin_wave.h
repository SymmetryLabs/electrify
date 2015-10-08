#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SinWave : public Waveform<Input> {

public:
    static void configure(SinWave<Input>& node, NodeHandle& handle);
    
    float calculate(const FrameContext& frame) const override;

private:
    NODE_IMPL();

};

REGISTER_NODE(SinWave);

#include "sin_wave.hpp"
