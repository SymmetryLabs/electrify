template<typename ClassType>
void NodeRegistrar::registerNode(const string& name)
{
    nodeFactories[name] = []() -> ClassType* {
        return Node::createNode<ClassType>();
    };
}

template<typename ClassType>
unique_ptr<ClassType> NodeRegistrar::getNode(const string& name) const
{
    return unique_ptr<ClassType>(dynamic_cast<ClassType*>(nodeFactories.at(name)()));
}
