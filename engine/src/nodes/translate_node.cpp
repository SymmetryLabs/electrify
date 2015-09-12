#include "translate_node.h"

TranslateNode::TranslateNode(NodeHandle& nodeHandle)
: ContextModifierNode(nodeHandle)
{
    nodeHandle.setName("Translate");
    nodeHandle.registerInput("translateX", &translateX);
    nodeHandle.registerInput("translateY", &translateY);
    nodeHandle.registerInput("translateZ", &translateZ);
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
