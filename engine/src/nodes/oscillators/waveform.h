#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class Waveform : public BasicNode<Skip<Input, 3>, float> {

public:
    virtual ~Waveform() = default;

    static void configure(Waveform<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 3>, float>::configure(node, handle);
        handle.registerInput("amplitude", node.generateInput(&node.amplitude, 1.0f));
        handle.registerInput("frequency", node.generateInput(&node.frequency, 1.0f));
        handle.registerInput("phase", node.generateInput(&node.phase));
    }

protected:
    Def<Input, 0, float> amplitude;
    Def<Input, 1, float> frequency;
    Def<Input, 2, float> phase;

private:
    NODE_IMPL_ABSTRACT();

};
