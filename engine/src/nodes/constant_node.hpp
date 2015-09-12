template <typename V>
ConstantNode<V>::ConstantNode(NodeHandle& nodeHandle, V value_)
: BasicNode<V>(nodeHandle)
, value(value_)
{
    nodeHandle.setName("Constant float");
}
