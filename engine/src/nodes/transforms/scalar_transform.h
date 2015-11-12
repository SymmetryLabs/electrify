#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class ScalarTransform : public BasicNode<Skip<Input, 1>, float> {

public:
    virtual ~ScalarTransform() = default;

    static void configure(ScalarTransform<Input>& node, NodeHandle& handle);

protected:
    Def<Input, 0, float> input;

private:
    NODE_IMPL();

};

#include "scalar_transform.hpp"
