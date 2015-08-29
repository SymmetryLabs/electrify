#pragma once
#include "globals.h"

#include "basic_node.h"

class TimeNode : public BasicNode<float> {

public:
    TimeNode();

    float calculate(const FrameContext& frame) const override;

};
