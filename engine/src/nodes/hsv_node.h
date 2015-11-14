#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template <typename Input>
class HsvNode : public BasicNode<Skip<Input, 3>, Color> {

public:
    static void configure(HsvNode<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 3>, Color>::configure(node, handle);
        handle.setName("HSV");
        handle.registerInput("hue", node.generateInput(&node.hue));
        handle.registerInput("saturation", node.generateInput(&node.saturation, 1.0f));
        handle.registerInput("value", node.generateInput(&node.value, 1.0f));
    }

    Color calculate(const FrameContext& frame) const override
    {
        Color in;
        in.fromHSV(hue(frame), saturation(frame), value(frame));
        return in;
    }

private:
    Def<Input, 0, float> hue;
    Def<Input, 1, float> saturation;
    Def<Input, 2, float> value;

    NODE_IMPL();

};

REGISTER_NODE(HsvNode);
