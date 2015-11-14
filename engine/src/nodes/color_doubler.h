#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template <typename Input>
class ColorDoubler : public BasicNode<Skip<Input, 1>, Color> {

public:
    static void configure(ColorDoubler<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 1>, Color>::configure(node, handle);
        handle.setName("Color doubler");
        handle.registerInput("color", node.generateInput(&node.colorInput));
    }

    Color calculate(const FrameContext& frame) const override
    {
        Color in = colorInput(frame);
        in.fromRGBA(in.asRGBA() * 2);
        return in;
    }

private:
    Def<Input, 0, Color> colorInput;

    NODE_IMPL();

};

REGISTER_NODE(ColorDoubler);
