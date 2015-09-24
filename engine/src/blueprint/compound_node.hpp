#include "node_registrar.h"

template<typename Input>
CompoundNode<Input>::CompoundNode(CompoundNodeHandle& nodeHandle)
: Node(nodeHandle)
{
    nodeHandle.setName("Compound node");
    nodeHandle.setSubnodeSlave(subnodes);
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

template<template<typename> class Type, typename HandleType, typename... Args>
HandleType* CompoundNodeHandle::makeSubnode(Args&&... args)
{
    auto subnodeHandle = makeNodeHandle<Type, HandleType>(forward<Args>(args)...);
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
