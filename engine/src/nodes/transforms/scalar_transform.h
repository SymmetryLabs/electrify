#pragma once
#include "globals.h"

#include "basic_node.h"

template<typename Input>
class ScalarTransform : public BasicNode<Skip<Input, 1>, float> {

public:
    virtual ~ScalarTransform() = default;

    static void configure(ScalarTransform<Input>& node, NodeHandle& handle);

    Def<Input, 0, float> input;

};

#include "scalar_transform.hpp"
