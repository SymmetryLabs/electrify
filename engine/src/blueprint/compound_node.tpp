#include "node_registrar.h"

template <typename Type, typename HandleType, typename... Args>
HandleType* CompoundNodeHandle::makeSubnode(Args&&... args)
{
    auto subnodeHandle = makeNodeHandle<Type, HandleType>(forward<Args>(args)...);
    auto subnodeHandlePtr = subnodeHandle.get();
    addSubnode(subnodeHandle);
    return subnodeHandlePtr;
}

template <typename V>
void CompoundNodeHandle::registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue)
{
    auto socket = make_unique<ProxySocket<V>>(inputAddr, defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}

template <typename V>
void CompoundNodeHandle::registerWirableOutput(const string& name, const V defaultValue)
{
    auto socket = make_unique<Socket<V>>(defaultValue);
    auto nodeSocket = make_shared<NodeSocket>(*this, name, move(socket));
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}
