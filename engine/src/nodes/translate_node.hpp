template<typename Input>
void TranslateNode<Input>::configure(TranslateNode<Input>& node, NodeHandle& handle)
{
    ContextModifierNode<Skip<Input, 3>>::configure(node, handle);
    handle.setName("Translate");
    handle.registerInput("translateX", node.generateInput(&node.translateX));
    handle.registerInput("translateY", node.generateInput(&node.translateY));
    handle.registerInput("translateZ", node.generateInput(&node.translateZ));
}

template<typename Input>
FrameContext TranslateNode<Input>::modifyContext(const FrameContext& original) const
{
    Pixel pixel {original.frag->pixel};
    pixel.x += translateX(original);
    pixel.y += translateY(original);
    pixel.z += translateZ(original);
    
    FragmentContext frag(pixel);
    FrameContext childFrame(original, &frag);
    return childFrame;
}
