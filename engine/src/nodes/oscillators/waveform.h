#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class Waveform : public BasicNode<Skip<Input, 3>, float> {

public:
    explicit Waveform(NodeHandle& nodeHandle);
    virtual ~Waveform() = default;

    Def<Input, 0, float> amplitude;
    Def<Input, 1, float> frequency;
    Def<Input, 2, float> phase;

};

#include "waveform.hpp"
