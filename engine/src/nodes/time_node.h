#pragma once
#include "globals.h"

#include "basic_node.h"

class TimeNode : public BasicNode<float> {

public:
    static const string nodeName() { return "Time"; }

    float calculate(const FrameContext& frame) const override;

};
