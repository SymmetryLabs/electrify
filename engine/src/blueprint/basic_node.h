#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"

template<typename Input, typename V>
class BasicNode : public Node {

public:
    virtual ~BasicNode() = default;

    static void configure(BasicNode<Input, V>& node, NodeHandle& handle);

    virtual V calculate(const FrameContext& frame) const = 0;

private:
    NODE_IMPL_ABSTRACT();

};

#include "basic_node.hpp"
