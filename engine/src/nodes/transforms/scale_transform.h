#pragma once
#include "globals.h"

#include "scalar_transform.h"

template<typename Input>
class ScaleTransform : public ScalarTransform<Skip<Input, 1>> {

public:
    explicit ScaleTransform(NodeHandle& nodeHandle);

    float calculate(const FrameContext& frame) const override;

    Def<Input, 0, float> multiplier;

};

#include "scale_transform.hpp"
