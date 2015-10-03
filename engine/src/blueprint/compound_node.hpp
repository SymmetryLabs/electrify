template<typename Input>
void CompoundNode<Input>::configure(CompoundNode<Input>& node, CompoundNodeHandle& handle)
{
    Node::configure(node, handle);
    handle.setName("Compound node");
    handle.setSubnodeSlave(node.subnodes);
}

template<typename Input>
void CompoundNode<Input>::init()
{
    for (const auto& subnode : subnodes) {
        subnode->init();
    }
}

template<typename Input>
void CompoundNode<Input>::deinit()
{
    for (const auto& subnode : subnodes) {
        subnode->deinit();
    }
}

template<typename Input>
void CompoundNode<Input>::update(const FrameContext& frame)
{
    for (const auto& subnode : subnodes) {
        subnode->update(frame);
    }
}

template<template<typename> class Type, typename HandleType>
HandleType* CompoundNodeHandle::makeSubnode(const string& name)
{
    auto subnodeHandle = makeNodeHandle<Type, HandleType>(name);
    auto subnodeHandlePtr = subnodeHandle.get();
    addSubnode(subnodeHandle);
    return subnodeHandlePtr;
}

template<typename V>
void CompoundNodeHandle::registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue)
{
    auto socket = make_unique<ProxySocket<V>>(inputAddr, defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}

template<typename V>
void CompoundNodeHandle::registerWirableOutput(const string& name, const V defaultValue)
{
    auto socket = make_unique<Socket<V>>(defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}
