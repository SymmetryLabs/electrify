#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input, typename V>
class ConstantNode : public BasicNode<Input, V> {

public:
    explicit ConstantNode(V value_ = V()) : value(value_) {}

    static void configure(ConstantNode<Input, V>& node, NodeHandle& handle)
    {
        BasicNode<Input, V>::configure(node, handle);
        handle.setName("Constant float");
    }

    V calculate(const FrameContext&) const override { return value; }

private:
    V value;

    NODE_IMPL();

};

template <typename Input>
using ConstantFloatNode = ConstantNode<Input, float>;

REGISTER_NODE(ConstantFloatNode);
