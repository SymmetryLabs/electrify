#include "node_socket.h"

#include "socket.h"

NodeSocket::NodeSocket(NodeHandle& nodeHandle_, const string& name_, const shared_ptr<BaseSocket>& socket_)
: NodeSignal(nodeHandle_, name_, dynamic_pointer_cast<BaseSignal>(socket_))
{
}

void NodeSocket::wireInput(weak_ptr<BaseSignal> sourceSignal)
{
    sendCommand<BaseSocket, BaseSignal>([] (shared_ptr<BaseSocket> socket, shared_ptr<BaseSignal> signal) {
        socket->setSignal(signal.get());
    }, sourceSignal);
}

void NodeSocket::unwireInput(weak_ptr<BaseSignal>)
{
    sendCommand<BaseSocket>([] (shared_ptr<BaseSocket> socket) {
        socket->setSignal(nullptr);
    });
}

void NodeSocket::registerContextModifier(ContextModifierChain& contextModifier)
{
    // getSocket()->addContextModifier(contextModifier);
}

void NodeSocket::unregisterContextModifier(ContextModifierChain& contextModifier)
{
    // getSocket()->removeContextModifier(contextModifier);
}
