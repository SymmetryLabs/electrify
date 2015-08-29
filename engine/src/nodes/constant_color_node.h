#pragma once
#include "globals.h"

#include "basic_node.h"

class ConstantColorNode : public BasicNode<Color> {

public:
    ConstantColorNode();

    Color calculate(const FrameContext& frame) const override;
    Color color = Color(0xFF0000FF);

};
