#pragma once
#include "globals.h"

#include "waveform.h"

template <typename Input>
class SinWave : public Waveform<Input> {

public:
    static void configure(SinWave<Input>& node, NodeHandle& handle)
    {
        Waveform<Input>::configure(node, handle);
        handle.setName("Sin wave");
    }

    float calculate(const FrameContext& frame) const override
    {
        return this->amplitude(frame) * (sin(M_2_PI * frame.timeSeconds() * this->frequency(frame) + this->phase(frame)) + 1) / 2;
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(SinWave);
