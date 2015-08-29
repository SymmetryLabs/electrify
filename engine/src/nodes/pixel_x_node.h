#pragma once
#include "globals.h"

#include "basic_node.h"

class PixelXNode : public BasicNode<float> {

public:
    PixelXNode();

    float calculate(const FrameContext& frame) const override;

};
