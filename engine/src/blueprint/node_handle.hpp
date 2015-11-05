template<template <typename> class NodeType>
NodeType<FunctionContainer>& NodeHandle::getNode()
{
    return dynamic_cast<NodeType<FunctionContainer>&>(*node);
}

template<typename T>
shared_ptr<T> NodeHandle::getSlave() const
{
    return dynamic_pointer_cast<T>(node);
}

template<template <typename> class NodeType, typename HandleType>
shared_ptr<HandleType> makeNodeHandle(const string& nodeName)
{
    auto handle = make_shared<HandleType>();
    handle->nodeName = nodeName;
    handle->postCtor();
    handle->postSharedPtrConstruction();
    return handle;
}

template<template<typename> class NodeType, typename HandleType>
void generateNodeForHandle(HandleType& handle)
{
    auto node = make_shared<NodeType<FunctionContainer>>();
    NodeType<FunctionContainer>::configure(*node, handle);
    handle.setNode(node);
}
