#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class TimeNode : public BasicNode<Input, float> {

public:
    static void configure(TimeNode<Input>& node, NodeHandle& handle)
    {
        BasicNode<Input, float>::configure(node, handle);
        handle.setName("Time");
    }

    float calculate(const FrameContext& frame) const override
    {
        return frame.timeSeconds();
    }

private:
    NODE_IMPL();

};

REGISTER_NODE(TimeNode);
