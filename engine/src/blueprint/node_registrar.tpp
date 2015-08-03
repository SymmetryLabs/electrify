template<typename ClassType>
void NodeRegistrar::registerNode()
{
  nodeFactories[ClassType::nodeName()] = []() -> ClassType* {
    return Node::createNode<ClassType>();
  };
}

template<typename ClassType>
unique_ptr<ClassType> NodeRegistrar::getNode(const string& name) const
{
  return unique_ptr<ClassType>(dynamic_cast<ClassType*>(nodeFactories.at(name)()));
}
