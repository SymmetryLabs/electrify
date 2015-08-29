template <typename V>
ConstantNode<V>::ConstantNode()
: BasicNode<V>("Constant float")
{
}

template <typename V>
ConstantNode<V>::ConstantNode(V value_)
: BasicNode<V>("Constant float")
, value(value_)
{
}
