#include "node_signal.h"

#include "node_socket.h"
#include "node_handle.h"

NodeSignal::NodeSignal(NodeHandle& nodeHandle_, const string& name_, const shared_ptr<BaseSignal>& signal_)
: DataTransmitter(signal_)
, nodeHandle(::shared_from_this<NodeHandle>(nodeHandle_))
, name(name_)
, signal(signal_)
{
}

NodeSignal::~NodeSignal() = default;

NodeHandle& NodeSignal::getNodeHandle() const
{
    return *nodeHandle.lock();
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
    destinationNodeSocket.wireInput(signal);
}

void NodeSignal::unwireOutput(NodeSocket& destinationNodeSocket)
{
    destinationNodeSocket.unwireInput(signal);
}

bool NodeSignal::belongsTo(const NodeHandle& nodeHandle_) const
{
    return &this->getNodeHandle() == &nodeHandle_;
}
