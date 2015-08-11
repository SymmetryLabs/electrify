#pragma once
#include "globals.h"

#include "basic_node.h"

class Waveform : public BasicNode<float> {

public:
    Waveform();
    virtual ~Waveform() {}

    SignalFunction<float> amplitude;
    SignalFunction<float> frequency;
    SignalFunction<float> phase;

};
