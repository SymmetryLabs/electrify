template<typename Input, typename V>
void ConstantNode<Input, V>::configure(ConstantNode<Input, V>& node, NodeHandle& handle)
{
    BasicNode<Input, V>::configure(node, handle);
    handle.setName("Constant float");
}

template<typename Input, typename V>
ConstantNode<Input, V>::ConstantNode(V value_)
: value(value_)
{
}
