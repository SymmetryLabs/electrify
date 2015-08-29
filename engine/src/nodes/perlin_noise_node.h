#pragma once
#include "globals.h"

#include <noise/module/perlin.h>

#include "basic_node.h"

class PerlinNoiseNode : public BasicNode<float> {

public:
    PerlinNoiseNode();

    float calculate(const FrameContext& frame) const override;

    SignalFunction<float> xInput;
    SignalFunction<float> yInput;
    SignalFunction<float> zInput;

    noise::module::Perlin noiseGenerator;

};
