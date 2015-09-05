#include "translate_node.h"

TranslateNode::TranslateNode()
: ContextModifierNode("Translate")
{
    registerInput("translateX", &translateX);
    registerInput("translateY", &translateY);
    registerInput("translateZ", &translateZ);
}

FrameContext TranslateNode::modifyContext(const FrameContext& original) const
{
    Pixel pixel {original.frag->pixel};
    pixel.x += translateX(original);
    pixel.y += translateY(original);
    pixel.z += translateZ(original);
    
    FragmentContext frag(pixel);
    FrameContext childFrame(original, &frag);
    return childFrame;
}
