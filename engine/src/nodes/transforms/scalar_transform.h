#pragma once
#include "globals.h"

#include "basic_node.h"

class ScalarTransform : public BasicNode<float> {

public:
    explicit ScalarTransform(NodeHandle& nodeHandle);
    virtual ~ScalarTransform() = default;

    SignalFunction<float> input;

};
