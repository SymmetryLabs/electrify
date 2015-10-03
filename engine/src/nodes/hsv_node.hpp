template<typename Input>
void HsvNode<Input>::configure(HsvNode<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 3>, Color>::configure(node, handle);
    handle.setName("HSV");
    handle.registerInput("hue", &node.hue);
    handle.registerInput("saturation", &node.saturation, 1.0f);
    handle.registerInput("value", &node.value, 1.0f);
}

template<typename Input>
Color HsvNode<Input>::calculate(const FrameContext& frame) const
{
    Color in;
    in.fromHSV(hue(frame), saturation(frame), value(frame));
    return in;
}
