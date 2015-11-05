#pragma once

#include "basic_node.h"
#include "color.h"

template<typename Input>
class TestNodeDestination : public BasicNode<Skip<Input, 1>, Color> {

public:
    static void configure(TestNodeDestination<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 1>, Color>::configure(node, handle);
        handle.registerInput("input", node.generateInput(&node.input));
    }

    Color calculate(const FrameContext& frame) const override
    {
        return input(frame);
    }

private:
    Def<Input, 0, Color> input;

    NODE_IMPL();

};

REGISTER_NODE(TestNodeDestination);
