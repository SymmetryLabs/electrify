#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template<typename Input>
class ColorDoubler : public BasicNode<Skip<Input, 1>, Color> {

public:
    explicit ColorDoubler(NodeHandle& nodeHandle);

    Color calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, Color> colorInput;

};

#include "color_doubler.hpp"
