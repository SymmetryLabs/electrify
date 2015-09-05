#pragma once
#include "globals.h"

#include "basic_node.h"

class ScalarTransform : public BasicNode<float> {

public:
    explicit ScalarTransform(const string& name);
    virtual ~ScalarTransform() = default;

    SignalFunction<float> input;

};
