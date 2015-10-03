#include "node_wire.h"

#include "node_socket.h"
#include "node_signal.h"
#include "node_handle.h"

NodeWire::NodeWire(NodeSignal& source_, NodeSocket& destination_)
: source(shared_from_this<NodeSignal>(source_))
, destination(shared_from_this<NodeSocket>(destination_))
{
    connect();
}

NodeWire::~NodeWire()
{
    if (connected) {
        disconnect();
    }
}

bool NodeWire::isConnected()
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
