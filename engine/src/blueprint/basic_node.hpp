template<typename Input, typename V>
void BasicNode<Input, V>::configure(BasicNode<Input, V>& node, NodeHandle& handle)
{
    Node::configure(node, handle);
    handle.registerOutput("output", node.generateOutput(&BasicNode::calculate, node));
}
