template<typename Input>
void ConstantColorNode<Input>::configure(ConstantColorNode<Input>& node, NodeHandle& handle)
{
    BasicNode<Input, Color>::configure(node, handle);
    handle.setName("Constant color");
}

template<typename Input>
Color ConstantColorNode<Input>::calculate(const FrameContext&) const
{
    return color;
}
