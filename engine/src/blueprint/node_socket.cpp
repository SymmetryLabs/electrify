#include "node_socket.h"

#include "socket.h"

NodeSocket::NodeSocket(NodeHandle& nodeHandle_, const string& name_, const shared_ptr<BaseSocket>& socket_)
: NodeSignal(nodeHandle_, name_, dynamic_pointer_cast<BaseSignal>(socket_))
{
}

void NodeSocket::wireInput(BaseSignal& sourceSignal)
{
    getSocket()->setSignal(&sourceSignal);
}

void NodeSocket::unwireInput(BaseSignal& sourceSignal)
{
    getSocket()->setSignal(nullptr);
}

void NodeSocket::registerContextModifier(ContextModifierChain& contextModifier)
{
    getSocket()->addContextModifier(contextModifier);
}

void NodeSocket::unregisterContextModifier(ContextModifierChain& contextModifier)
{
    getSocket()->removeContextModifier(contextModifier);
}

BaseSocket* NodeSocket::getSocket() const
{
    return dynamic_cast<BaseSocket*>(getSignal());
}
