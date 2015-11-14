#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template <typename Input>
class Incrementer : public BasicNode<Skip<Input, 1>, Color> {

public:
    static void configure(Incrementer<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 1>, Color>::configure(node, handle);
        handle.setName("Incrementer");
        handle.registerInput("color", node.generateInput(&node.colorInput));
    }

    virtual void init() override
    {
        increment = 0;
    }

    virtual void update(const FrameContext& frame) override
    {
        increment = (increment + 0x100) % 0x10000;
    }

    Color calculate(const FrameContext& frame) const override
    {
        Color in = colorInput(frame);
        in.fromRGBA(in.asRGBA() + increment);
        return in;
    }

private:
    Def<Input, 0, Color> colorInput;

    int increment = 0;

    NODE_IMPL();

};

REGISTER_NODE(Incrementer);
