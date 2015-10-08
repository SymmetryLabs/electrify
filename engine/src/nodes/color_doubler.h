#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template<typename Input>
class ColorDoubler : public BasicNode<Skip<Input, 1>, Color> {

public:
    static void configure(ColorDoubler<Input>& node, NodeHandle& handle);

    Color calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, Color> colorInput;

    NODE_IMPL();

};

REGISTER_NODE(ColorDoubler);

#include "color_doubler.hpp"
