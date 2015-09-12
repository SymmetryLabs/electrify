#pragma once
#include "globals.h"

#include "basic_node.h"

class PixelXNode : public BasicNode<float> {

public:
    explicit PixelXNode(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

};
