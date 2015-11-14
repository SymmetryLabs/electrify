#pragma once
#include "globals.h"

#include "waveform.h"

template <typename Input>
class SawWave : public Waveform<Input> {

public:
    static void configure(SawWave<Input>& node, NodeHandle& handle)
    {
        Waveform<Input>::configure(node, handle);
        handle.setName("Sawtooth wave");
    }

    float calculate(const FrameContext& frame) const override
    {
        float unused;
        return this->amplitude(frame) * modf(frame.timeSeconds() * this->frequency(frame) + this->phase(frame), &unused);
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(SawWave);
