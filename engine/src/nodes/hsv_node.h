#pragma once
#include "globals.h"

#include "basic_node.h"

class HsvNode : public BasicNode<Color> {

public:
    HsvNode();

    static const string nodeName() { return "HSV"; }

    Color calculate(const FrameContext& frame) const override;
    
    SignalFunction<float> hue;
    SignalFunction<float> saturation;
    SignalFunction<float> value;

};
