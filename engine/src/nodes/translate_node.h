#pragma once
#include "globals.h"

#include "context_modifier_node.h"

template <typename Input>
class TranslateNode : public ContextModifierNode<Skip<Input, 3>> {

public:
    static void configure(TranslateNode<Input>& node, NodeHandle& handle)
    {
        ContextModifierNode<Skip<Input, 3>>::configure(node, handle);
        handle.setName("Translate");
        handle.registerInput("translateX", node.generateInput(&node.translateX));
        handle.registerInput("translateY", node.generateInput(&node.translateY));
        handle.registerInput("translateZ", node.generateInput(&node.translateZ));
    }

    FrameContext modifyContext(const FrameContext& original) const override
    {
        Pixel pixel {original.frag->pixel};
        pixel.x += translateX(original);
        pixel.y += translateY(original);
        pixel.z += translateZ(original);

        FragmentContext frag(pixel);
        FrameContext childFrame(original, &frag);
        return childFrame;
    }

private:
    Def<Input, 0, float> translateX;
    Def<Input, 1, float> translateY;
    Def<Input, 2, float> translateZ;

    NODE_IMPL();

};

REGISTER_NODE(TranslateNode);
