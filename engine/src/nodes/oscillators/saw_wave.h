#pragma once
#include "globals.h"

#include "waveform.h"

template <typename Input>
class SawWave : public Waveform<Input> {

public:
    static void configure(SawWave<Input>& node, NodeHandle& handle);

    float calculate(const FrameContext& frame) const override;

private:
    NODE_IMPL();

};

REGISTER_NODE(SawWave);

#include "saw_wave.hpp"
