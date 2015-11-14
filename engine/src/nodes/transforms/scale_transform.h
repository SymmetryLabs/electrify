#pragma once
#include "globals.h"

#include "scalar_transform.h"

template <typename Input>
class ScaleTransform : public ScalarTransform<Skip<Input, 1>> {

public:
    static void configure(ScaleTransform<Input>& node, NodeHandle& handle)
    {
        ScalarTransform<Skip<Input, 1>>::configure(node, handle);
        handle.setName("Scale");
        handle.registerInput("multiplier", node.generateInput(&node.multiplier, 1.0f));
    }

    float calculate(const FrameContext& frame) const override
    {
        return this->multiplier(frame) * this->input(frame);
    }

private:
    Def<Input, 0, float> multiplier;

    NODE_IMPL();

};

REGISTER_NODE(ScaleTransform);
