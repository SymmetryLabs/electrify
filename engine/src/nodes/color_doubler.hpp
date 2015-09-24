template<typename Input>
ColorDoubler<Input>::ColorDoubler(NodeHandle& nodeHandle)
: BasicNode<Input, Color>(nodeHandle)
{
    nodeHandle.setName("Color doubler");
    nodeHandle.registerInput("color", &colorInput);
}

template<typename Input>
Color ColorDoubler<Input>::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() * 2);
    return in;
}
