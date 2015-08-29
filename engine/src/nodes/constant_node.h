#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename V>
class ConstantNode : public BasicNode<V> {

public:
    ConstantNode();
    explicit ConstantNode(V value);

    V calculate(const FrameContext&) const override { return value; }

private:
    V value;

};

typedef ConstantNode<float> ConstantFloatNode;

#include "constant_node.hpp"
