template<typename NodeType, typename HandleType>
void NodeRegistrar::registerNode(const string& name)
{
    nodeFactories[name] = [] {
        return makeNodeHandle<NodeType, HandleType>();
    };
}
