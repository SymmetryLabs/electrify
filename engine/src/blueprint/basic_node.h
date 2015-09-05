#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"

template <typename V>
class BasicNode : public Node {

public:
    explicit BasicNode(const string& name);
    virtual ~BasicNode() = default;

    virtual V calculate(const FrameContext& frame) const = 0;

};

#include "basic_node.tpp"
