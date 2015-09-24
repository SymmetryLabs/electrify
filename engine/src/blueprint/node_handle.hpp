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

// template<typename Archive>
// void NodeHandle::serialize(Archive& archive)
// {

// }

template<typename NodeType>
NodeType& NodeHandle::getNode()
{
    return dynamic_cast<NodeType&>(*node);
}

template<template <typename> class NodeType, typename HandleType, typename... Args>
shared_ptr<HandleType> makeNodeHandle(Args&&... args)
{
    auto handle = make_shared<HandleType>();
    handle->setNode(make_shared<NodeType<FunctionContainer>>(*handle, forward<Args>(args)...));
    return handle;
}
