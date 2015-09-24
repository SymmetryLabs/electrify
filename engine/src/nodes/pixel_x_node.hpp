template<typename Input>
PixelXNode<Input>::PixelXNode(NodeHandle& nodeHandle)
: BasicNode<Input, float>(nodeHandle)
{
    nodeHandle.setName("Pixel.x");
}

template<typename Input>
float PixelXNode<Input>::calculate(const FrameContext& frame) const
{
    return frame.frag->pixel.x;
}
