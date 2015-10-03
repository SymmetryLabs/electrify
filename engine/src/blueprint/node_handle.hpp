template<typename V>
void NodeHandle::registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue)
{
    registerInput(name, make_shared<ProxySocket<V>>(inputAddr, defaultValue));
}

template<typename V, typename C>
void NodeHandle::registerOutput(const string& name, V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst)
{
    registerOutput(name, make_shared<FunctionSignal<V>>(calculate_function_, inst));
}

template<typename NodeType>
NodeType& NodeHandle::getNode()
{
    return dynamic_cast<NodeType&>(*node);
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
