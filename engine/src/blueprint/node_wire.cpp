#include "node_wire.h"

#include "node_socket.h"
#include "node_signal.h"
#include "node_handle.h"

NodeWire::NodeWire(NodeSignal& source_, NodeSocket& destination_)
: source(shared_from_this<NodeSignal>(source_))
, destination(shared_from_this<NodeSocket>(destination_))
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
    return source.lock().get();
}

NodeSocket* NodeWire::getDestination() const
{
    return destination.lock().get();
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
        if (auto sourcePtr = strongSourceHandle->getOutput(sourceName)) {
            source = shared_from_this<NodeSignal>(*sourcePtr);
        }
    }
    if (auto strongDestinationHandle = destinationHandle.lock()) {
        if (auto destinationPtr = strongDestinationHandle->getOutput(destinationName)) {
            destination = shared_from_this<NodeSocket>(*destinationPtr);
        }
    }
}
