#pragma once
#include "globals.h"

#include "basic_node.h"

class Waveform : public BasicNode<float> {

public:
    explicit Waveform(const string& name);
    virtual ~Waveform() = default;

    SignalFunction<float> amplitude;
    SignalFunction<float> frequency;
    SignalFunction<float> phase;

};
