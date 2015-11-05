template<typename Input>
void ScaleTransform<Input>::configure(ScaleTransform<Input>& node, NodeHandle& handle)
{
    ScalarTransform<Skip<Input, 1>>::configure(node, handle);
    handle.setName("Scale");
    handle.registerInput("multiplier", node.generateInput(&node.multiplier, 1.0f));
}

template<typename Input>
float ScaleTransform<Input>::calculate(const FrameContext& frame) const
{
    return this->multiplier(frame) * this->input(frame);
}
