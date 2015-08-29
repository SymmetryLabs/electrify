template <typename V>
BasicNode<V>::BasicNode(const string& name)
: Node(name)
{
    registerOutput("output", &BasicNode::calculate);
}
