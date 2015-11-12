#pragma once
#include "globals.h"

#include <noise/module/perlin.h>

#include "basic_node.h"

template <typename Input>
class PerlinNoiseNode : public BasicNode<Skip<Input, 3>, float> {

public:
    static void configure(PerlinNoiseNode<Input>& node, NodeHandle& handle);

    float calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, float> xInput;
    Def<Input, 1, float> yInput;
    Def<Input, 2, float> zInput;

    noise::module::Perlin noiseGenerator;

    NODE_IMPL();

};

REGISTER_NODE(PerlinNoiseNode);

#include "perlin_noise_node.hpp"
