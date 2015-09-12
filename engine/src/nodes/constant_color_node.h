#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

class ConstantColorNode : public BasicNode<Color> {

public:
    explicit ConstantColorNode(NodeHandle& nodeHandle);

    Color calculate(const FrameContext& frame) const override;
    Color color = Color(0xFF0000FF);

};
