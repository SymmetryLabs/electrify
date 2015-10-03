#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template<typename Input>
class ConstantColorNode : public BasicNode<Input, Color> {

public:
    static void configure(ConstantColorNode<Input>& node, NodeHandle& handle);

    Color calculate(const FrameContext& frame) const override;
    Color color = Color(0xFF0000FF);

};

#include "constant_color_node.hpp"
