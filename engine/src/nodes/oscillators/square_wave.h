#pragma once
#include "globals.h"

#include "waveform.h"

template<typename Input>
class SquareWave : public Waveform<Input> {

public:
    static void configure(SquareWave<Input>& node, NodeHandle& handle);
    
    float calculate(const FrameContext& frame) const override;

private:
    NODE_IMPL();

};

REGISTER_NODE(SquareWave);

#include "square_wave.hpp"
