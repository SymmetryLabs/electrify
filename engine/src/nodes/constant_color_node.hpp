template<typename Input>
ConstantColorNode<Input>::ConstantColorNode(NodeHandle& nodeHandle)
: BasicNode<Input, Color>(nodeHandle)
{
    nodeHandle.setName("Constant color");
}

template<typename Input>
Color ConstantColorNode<Input>::calculate(const FrameContext&) const
{
    return color;
}
