#pragma once
#include "globals.h"

#include "scalar_transform.h"

template <typename Input>
class ScaleTransform : public ScalarTransform<Skip<Input, 1>> {

public:
    static void configure(ScaleTransform<Input>& node, NodeHandle& handle);

    float calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, float> multiplier;

    NODE_IMPL();

};

REGISTER_NODE(ScaleTransform);

#include "scale_transform.hpp"
