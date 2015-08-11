#pragma once
#include "globals.h"

#include "context_modifier_node.h"

class TranslateNode : public ContextModifierNode {

public:
    TranslateNode();

    static const string nodeName() { return "Translate"; }

    FrameContext modifyContext(const FrameContext& original) override;

private:
    SignalFunction<float> translateX;
    SignalFunction<float> translateY;
    SignalFunction<float> translateZ;

};
