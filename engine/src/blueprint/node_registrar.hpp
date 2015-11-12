template <template <typename> class NodeType, typename HandleType>
void NodeRegistrar::registerNode(const string& name)
{
    nodeHandleFactories[name] = [=] {
        return makeNodeHandle<NodeType, HandleType>(name);
    };
    nodeFactories[name] = [this] (NodeHandle& handle_) {
        auto& handle = dynamic_cast<HandleType&>(handle_);
        generateNodeForHandle<NodeType>(handle);
    };
}
