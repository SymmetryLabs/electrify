#include "node_signal.h"

#include "node_socket.h"
#include "node.h"

NodeSignal::NodeSignal(Node& node_, const string& name_, unique_ptr<BaseSignal>&& signal_)
: node(node_)
, name(name_)
, signal(move(signal_))
{
}

string NodeSignal::getName() const
{
    return name.getValue();
}

BaseSignal* NodeSignal::getSignal() const
{
    return signal.get();
}

void NodeSignal::wireOutput(NodeSocket& destinationNodeSocket)
{
    destinationNodeSocket.wireInput(*getSignal());
}

void NodeSignal::unwireOutput(NodeSocket& destinationNodeSocket)
{
    destinationNodeSocket.unwireInput(*getSignal());
}

NodeSignalProxy::NodeSignalProxy(shared_ptr<NodeSignal> master, ProxyBridge& proxyBridge)
: DataProxy(master, proxyBridge)
{
    this->node = master->node.getProxy<NodeProxy>(proxyBridge);
    this->bind(master->name, this->name);
}
