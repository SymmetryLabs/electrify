#include "node_signal.h"

#include "node_socket.h"
#include "node_handle.h"

NodeSignal::NodeSignal(NodeHandle& nodeHandle_, const string& name_, const shared_ptr<BaseSignal>& signal_)
: DataTransmitter(signal_)
, nodeHandle(nodeHandle_)
, name(name_)
, signal(signal_)
{
}

NodeSignal::~NodeSignal() = default;

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
