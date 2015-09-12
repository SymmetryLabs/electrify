template <typename V>
BasicNode<V>::BasicNode(NodeHandle& nodeHandle)
: Node(nodeHandle)
{
    nodeHandle.registerOutput("output", &BasicNode::calculate, *this);
}
