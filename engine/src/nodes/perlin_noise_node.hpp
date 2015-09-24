template<typename Input>
PerlinNoiseNode<Input>::PerlinNoiseNode(NodeHandle& nodeHandle)
: BasicNode<Input, float>(nodeHandle)
{
    nodeHandle.setName("Perlin noise");
    nodeHandle.registerInput("xInput", &xInput);
    nodeHandle.registerInput("yInput", &yInput);
    nodeHandle.registerInput("zInput", &zInput);
}

template<typename Input>
float PerlinNoiseNode<Input>::calculate(const FrameContext& frame) const
{
    return noiseGenerator.GetValue(xInput(frame), yInput(frame), zInput(frame));
}
