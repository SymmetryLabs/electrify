template<typename Input>
ScalarTransform<Input>::ScalarTransform(NodeHandle& nodeHandle)
: BasicNode<Input, float>(nodeHandle)
{
    nodeHandle.registerInput("input", &input);
}
