#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input, typename V>
class ConstantNode : public BasicNode<Input, V> {

public:
    explicit ConstantNode(NodeHandle& nodeHandle, V value = V());

    V calculate(const FrameContext&) const override { return value; }

private:
    V value;

};

template<typename Input>
using ConstantFloatNode = ConstantNode<Input, float>;

#include "constant_node.hpp"
