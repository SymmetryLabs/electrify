#pragma once
#include "globals.h"

#include "basic_node.h"

class TimeNode : public BasicNode<float> {

public:
    explicit TimeNode(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

};
