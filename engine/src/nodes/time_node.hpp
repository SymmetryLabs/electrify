template <typename Input>
void TimeNode<Input>::configure(TimeNode<Input>& node, NodeHandle& handle)
{
    BasicNode<Input, float>::configure(node, handle);
    handle.setName("Time");
}

template <typename Input>
float TimeNode<Input>::calculate(const FrameContext& frame) const
{
    return frame.timeSeconds();
}
