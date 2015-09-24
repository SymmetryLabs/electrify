#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class TimeNode : public BasicNode<Input, float> {

public:
    explicit TimeNode(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

};

#include "time_node.hpp"
