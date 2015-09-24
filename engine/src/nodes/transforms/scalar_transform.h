#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class ScalarTransform : public BasicNode<Skip<Input, 1>, float> {

public:
    explicit ScalarTransform(NodeHandle& nodeHandle);
    virtual ~ScalarTransform() = default;

    Def<Input, 0, float> input;

};

#include "scalar_transform.hpp"
