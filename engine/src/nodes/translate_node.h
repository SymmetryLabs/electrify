#pragma once
#include "globals.h"

#include "context_modifier_node.h"

template<typename Input>
class TranslateNode : public ContextModifierNode<Skip<Input, 3>> {

public:
    static void configure(TranslateNode<Input>& node, NodeHandle& handle);

    FrameContext modifyContext(const FrameContext& original) const override;

private:
    Def<Input, 0, float> translateX;
    Def<Input, 1, float> translateY;
    Def<Input, 2, float> translateZ;

    NODE_IMPL();

};

REGISTER_NODE(TranslateNode);

#include "translate_node.hpp"
