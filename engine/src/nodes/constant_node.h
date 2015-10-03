#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input, typename V>
class ConstantNode : public BasicNode<Input, V> {

public:
    explicit ConstantNode(V value = V());

    static void configure(ConstantNode<Input, V>& node, NodeHandle& handle);

    V calculate(const FrameContext&) const override { return value; }

private:
    V value;

};

template<typename Input>
using ConstantFloatNode = ConstantNode<Input, float>;

REGISTER_NODE(ConstantFloatNode);

#include "constant_node.hpp"
