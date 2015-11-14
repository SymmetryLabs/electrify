#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class PixelXNode : public BasicNode<Input, float> {

public:
    static void configure(PixelXNode<Input>& node, NodeHandle& handle)
    {
        BasicNode<Input, float>::configure(node, handle);
        handle.setName("Pixel.x");
    }

    float calculate(const FrameContext& frame) const override
    {
        return frame.frag->pixel.x;
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(PixelXNode);
