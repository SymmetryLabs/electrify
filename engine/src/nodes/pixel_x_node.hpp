template<typename Input>
void PixelXNode<Input>::configure(PixelXNode<Input>& node, NodeHandle& handle)
{
    BasicNode<Input, float>::configure(node, handle);
    handle.setName("Pixel.x");
}

template<typename Input>
float PixelXNode<Input>::calculate(const FrameContext& frame) const
{
    return frame.frag->pixel.x;
}
