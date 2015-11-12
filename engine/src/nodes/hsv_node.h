#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template <typename Input>
class HsvNode : public BasicNode<Skip<Input, 3>, Color> {

public:
    static void configure(HsvNode<Input>& node, NodeHandle& handle);

    Color calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, float> hue;
    Def<Input, 1, float> saturation;
    Def<Input, 2, float> value;

    NODE_IMPL();

};

REGISTER_NODE(HsvNode);

#include "hsv_node.hpp"
