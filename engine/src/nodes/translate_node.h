#pragma once
#include "globals.h"

#include "context_modifier_node.h"

class TranslateNode : public ContextModifierNode {

public:
    explicit TranslateNode(NodeHandle& nodeHandle);

    FrameContext modifyContext(const FrameContext& original) const override;

private:
    SignalFunction<float> translateX;
    SignalFunction<float> translateY;
    SignalFunction<float> translateZ;

};
