#pragma once
#include "globals.h"

#include <noise/module/perlin.h>

#include "basic_node.h"

template <typename Input>
class PerlinNoiseNode : public BasicNode<Skip<Input, 3>, float> {

public:
    static void configure(PerlinNoiseNode<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 3>, float>::configure(node, handle);
        handle.setName("Perlin noise");
        handle.registerInput("xInput", node.generateInput(&node.xInput));
        handle.registerInput("yInput", node.generateInput(&node.yInput));
        handle.registerInput("zInput", node.generateInput(&node.zInput));
    }

    float calculate(const FrameContext& frame) const override
    {
        return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
    }

private:
    Def<Input, 0, float> xInput;
    Def<Input, 1, float> yInput;
    Def<Input, 2, float> zInput;

    noise::module::Perlin noiseGenerator;

    NODE_IMPL();

};

REGISTER_NODE(PerlinNoiseNode);
