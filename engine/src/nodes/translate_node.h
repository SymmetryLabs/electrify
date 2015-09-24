#pragma once
#include "globals.h"

#include "context_modifier_node.h"

template<typename Input>
class TranslateNode : public ContextModifierNode<Skip<Input, 3>> {

public:
    explicit TranslateNode(NodeHandle& nodeHandle);

    FrameContext modifyContext(const FrameContext& original) const override;

private:
    Def<Input, 0, float> translateX;
    Def<Input, 1, float> translateY;
    Def<Input, 2, float> translateZ;

};

#include "translate_node.hpp"
