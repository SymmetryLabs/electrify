template<typename Input, typename V>
ConstantNode<Input, V>::ConstantNode(NodeHandle& nodeHandle, V value_)
: BasicNode<Input, V>(nodeHandle)
, value(value_)
{
    nodeHandle.setName("Constant float");
}
