#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"

template <typename V>
class BasicNode : public Node {

public:
    BasicNode();
    virtual ~BasicNode() {}

    virtual V calculate(const FrameContext& frame) const = 0;

};

#include "basic_node.tpp"
