template<typename Input>
HsvNode<Input>::HsvNode(NodeHandle& nodeHandle)
: BasicNode<Input, Color>(nodeHandle)
{
    nodeHandle.setName("HSV");
    nodeHandle.registerInput("hue", &hue);
    nodeHandle.registerInput("saturation", &saturation, 1.0f);
    nodeHandle.registerInput("value", &value, 1.0f);
}

template<typename Input>
Color HsvNode<Input>::calculate(const FrameContext& frame) const
{
    Color in;
    in.fromHSV(hue(frame), saturation(frame), value(frame));
    return in;
}
