#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class TimeNode : public BasicNode<Input, float> {

public:
    static void configure(TimeNode<Input>& node, NodeHandle& handle);

    float calculate(const FrameContext& frame) const override;

};

REGISTER_NODE(TimeNode);

#include "time_node.hpp"
