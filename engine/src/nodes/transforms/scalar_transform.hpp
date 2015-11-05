template<typename Input>
void ScalarTransform<Input>::configure(ScalarTransform<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 1>, float>::configure(node, handle);
    handle.registerInput("input", node.generateInput(&node.input));
}
