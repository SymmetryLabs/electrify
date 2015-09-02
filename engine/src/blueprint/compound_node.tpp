#include "node_registrar.h"

template <typename Type, typename... Targs>
Type* CompoundNode::makeSubnode(Targs&&... Fargs)
{
    auto subnode = unique_ptr<Type>(Node::createNode<Type>(forward<Targs>(Fargs)...));
    auto subnodePtr = subnode.get();
    addSubnode(move(subnode));
    return subnodePtr;
}

template <typename V>
void CompoundNode::registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue)
{
    auto socket = make_unique<ProxySocket<V>>(inputAddr, defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}

template <typename V>
void CompoundNode::registerWirableOutput(const string& name, const V defaultValue)
{
    auto socket = make_unique<Socket<V>>(defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}
