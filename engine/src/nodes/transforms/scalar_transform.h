#pragma once
#include "globals.h"

#include "basic_node.h"

template <typename Input>
class ScalarTransform : public BasicNode<Skip<Input, 1>, float> {

public:
    virtual ~ScalarTransform() = default;

    static void configure(ScalarTransform<Input>& node, NodeHandle& handle)
    {
        BasicNode<Skip<Input, 1>, float>::configure(node, handle);
        handle.registerInput("input", node.generateInput(&node.input));
    }

protected:
    Def<Input, 0, float> input;

private:
    NODE_IMPL();

};
