#pragma once

#include "basic_node.h"
#include "color.h"

template<typename Input>
class TestNodeSource : public BasicNode<Input, Color> {

public:
    static void configure(TestNodeSource<Input>& node, NodeHandle& handle)
    {
        BasicNode<Input, Color>::configure(node, handle);
    }

    Color calculate(const FrameContext& frame) const override
    {
        return Color(0xFF0000FF);
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(TestNodeSource);
