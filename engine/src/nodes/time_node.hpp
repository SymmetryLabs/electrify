template<typename Input>
TimeNode<Input>::TimeNode(NodeHandle& nodeHandle)
: BasicNode<Input, float>(nodeHandle)
{
    nodeHandle.setName("Time");
}

template<typename Input>
float TimeNode<Input>::calculate(const FrameContext& frame) const
{
    return frame.timeSeconds();
}
