#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template <typename Input>
class ConstantColorNode : public BasicNode<Input, Color> {

public:
    static void configure(ConstantColorNode<Input>& node, NodeHandle& handle)
    {
        BasicNode<Input, Color>::configure(node, handle);
        handle.setName("Constant color");
    }

    Color calculate(const FrameContext& frame) const override
    {
        return color;
    }

private:
    Color color = Color(0xFF0000FF);

    NODE_IMPL();

};

REGISTER_NODE(ConstantColorNode);
