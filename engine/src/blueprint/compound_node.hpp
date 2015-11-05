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

template<typename Input>
size_t CompoundNode<Input>::getNumSubnodes() const
{
    return subnodes.size();
}

template<typename Input>
template<typename V>
shared_ptr<BaseSocket> CompoundNode<Input>::generateWirableOutput(SignalFunction<V>* inputAddr, const V defaultValue)
{
    auto socket = make_shared<ProxySocket<V>>(inputAddr, defaultValue);
    wirableOutputs.push_back(socket);
    return socket;
}

template<typename Input>
template<typename V>
shared_ptr<BaseSocket> CompoundNode<Input>::generateWirableOutput(const V defaultValue)
{
    auto socket = make_shared<Socket<V>>(defaultValue);
    wirableOutputs.push_back(socket);
    return socket;
}

template<template<typename> class Type, typename HandleType>
HandleType* CompoundNodeHandle::makeSubnode(const string& name)
{
    auto subnodeHandle = makeNodeHandle<Type, HandleType>(name);
    auto subnodeHandlePtr = subnodeHandle.get();
    addSubnode(subnodeHandle);
    return subnodeHandlePtr;
}
