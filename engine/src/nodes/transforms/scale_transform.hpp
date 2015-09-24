template<typename Input>
ScaleTransform<Input>::ScaleTransform(NodeHandle& nodeHandle)
: ScalarTransform<Input>(nodeHandle)
{
    nodeHandle.setName("Scale");
    nodeHandle.registerInput("multiplier", &multiplier, 1.0f);
}

template<typename Input>
float ScaleTransform<Input>::calculate(const FrameContext& frame) const
{
    return this->multiplier(frame) * this->input(frame);
}
