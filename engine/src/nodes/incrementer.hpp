template <typename Input>
void Incrementer<Input>::configure(Incrementer<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 1>, Color>::configure(node, handle);
    handle.setName("Incrementer");
    handle.registerInput("color", node.generateInput(&node.colorInput));
}

template <typename Input>
void Incrementer<Input>::init()
{
    increment = 0;
}

template <typename Input>
void Incrementer<Input>::update(const FrameContext& frame)
{
    increment = (increment + 0x100) % 0x10000;
}

template <typename Input>
Color Incrementer<Input>::calculate(const FrameContext& frame) const
{
    Color in = colorInput(frame);
    in.fromRGBA(in.asRGBA() + increment);
    return in;
}
