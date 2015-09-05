#include "node_socket.h"

NodeSocket::NodeSocket(Node& node_, const string& name_, unique_ptr<BaseSocket>&& socket_)
: NodeSignal(node_, name_, nullptr)
, socket(move(socket_))
{
}

BaseSignal* NodeSocket::getSignal() const
{
    return dynamic_cast<BaseSignal*>(socket.get());
}

void NodeSocket::wireInput(BaseSignal& sourceSignal)
{
    socket->setSignal(&sourceSignal);
}

void NodeSocket::unwireInput(BaseSignal& sourceSignal)
{
    socket->setSignal(nullptr);
}

void NodeSocket::registerContextModifier(ContextModifierChain& contextModifier)
{
    socket->addContextModifier(contextModifier);
}

void NodeSocket::unregisterContextModifier(ContextModifierChain& contextModifier)
{
    socket->removeContextModifier(contextModifier);
}

NodeSocketProxy::NodeSocketProxy(shared_ptr<NodeSocket> master, ProxyBridge& proxyBridge)
: NodeSignalProxy(master, proxyBridge)
{
}
