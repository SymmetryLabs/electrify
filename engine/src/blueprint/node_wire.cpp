#include "node_wire.h"

#include "node_socket.h"
#include "node_signal.h"
#include "node_handle.h"

NodeWire::NodeWire(NodeSignal& source_, NodeSocket& destination_)
: source(&source_)
, destination(&destination_)
, sourceHandle(shared_from_this<NodeHandle>(source_.getNodeHandle()))
, destinationHandle(shared_from_this<NodeHandle>(destination_.getNodeHandle()))
, sourceName(source_.getName())
, destinationName(destination_.getName())
{
    connect();
}

NodeWire::~NodeWire()
{
    if (connected) {
        disconnect();
    }
}

bool NodeWire::isConnected() const
{
    return connected;
}

void NodeWire::connect()
{
    auto source = getSource();
    auto destination = getDestination();
    if (source && destination) {
        connected = true;
        source->wireOutput(*destination);
    }
}

void NodeWire::disconnect()
{
    connected = false;
    auto source = getSource();
    auto destination = getDestination();
    if (source && destination) {
        source->unwireOutput(*destination);
    }
}

NodeSignal* NodeWire::getSource() const
{
    return source;
}

NodeSocket* NodeWire::getDestination() const
{
    return destination;
}

bool NodeWire::isAssignedTo(const NodeHandle& nodeHandle) const
{
    auto source = getSource();
    auto destination = getDestination();
    return (source && source->belongsTo(nodeHandle))
        || (destination && destination->belongsTo(nodeHandle));
}

void NodeWire::populateSignals()
{
    if (auto strongSourceHandle = sourceHandle.lock()) {
        source = strongSourceHandle->getOutput(sourceName);
    }
    if (auto strongDestinationHandle = destinationHandle.lock()) {
        destination = strongDestinationHandle->getInput(destinationName);
    }
}
