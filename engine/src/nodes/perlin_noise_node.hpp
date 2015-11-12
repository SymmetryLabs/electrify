template <typename Input>
void PerlinNoiseNode<Input>::configure(PerlinNoiseNode<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 3>, float>::configure(node, handle);
    handle.setName("Perlin noise");
    handle.registerInput("xInput", node.generateInput(&node.xInput));
    handle.registerInput("yInput", node.generateInput(&node.yInput));
    handle.registerInput("zInput", node.generateInput(&node.zInput));
}

template <typename Input>
float PerlinNoiseNode<Input>::calculate(const FrameContext& frame) const
{
    return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
}
