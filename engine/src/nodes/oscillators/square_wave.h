#pragma once
#include "globals.h"

#include "waveform.h"

template <typename Input>
class SquareWave : public Waveform<Input> {

public:
    static void configure(SquareWave<Input>& node, NodeHandle& handle)
    {
        Waveform<Input>::configure(node, handle);
        handle.setName("Square wave");
    }

    float calculate(const FrameContext& frame) const override
    {
        return this->amplitude(frame) * floor(2 * frame.timeSeconds() * this->frequency(frame) + this->phase(frame));
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(SquareWave);
