#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class PixelXNode : public BasicNode<Input, float> {

public:
    explicit PixelXNode(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

};

#include "pixel_x_node.hpp"
