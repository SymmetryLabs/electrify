template <typename Input>
void ColorDoubler<Input>::configure(ColorDoubler<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 1>, Color>::configure(node, handle);
    handle.setName("Color doubler");
    handle.registerInput("color", node.generateInput(&node.colorInput));
}

template <typename Input>
Color ColorDoubler<Input>::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() * 2);
    return in;
}
