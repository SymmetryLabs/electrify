#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class PixelXNode : public BasicNode<Input, float> {

public:
    static void configure(PixelXNode<Input>& node, NodeHandle& handle);

    float calculate(const FrameContext& frame) const override;

private:
    NODE_IMPL();

};

REGISTER_NODE(PixelXNode);

#include "pixel_x_node.hpp"
