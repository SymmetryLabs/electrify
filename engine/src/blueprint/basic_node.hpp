template<typename Input, typename V>
BasicNode<Input, V>::BasicNode(NodeHandle& nodeHandle)
: Node(nodeHandle)
{
    nodeHandle.registerOutput("output", &BasicNode::calculate, *this);
}
