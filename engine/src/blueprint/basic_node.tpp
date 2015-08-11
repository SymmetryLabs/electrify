template <typename V>
BasicNode<V>::BasicNode()
{
    registerOutput("output", &BasicNode::calculate);
}
