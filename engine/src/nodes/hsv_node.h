#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

class HsvNode : public BasicNode<Color> {

public:
    explicit HsvNode(NodeHandle& nodeHandle);

    Color calculate(const FrameContext& frame) const override;
    
    SignalFunction<float> hue;
    SignalFunction<float> saturation;
    SignalFunction<float> value;

};
