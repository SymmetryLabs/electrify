#include "node_wire.h"

NodeWire::NodeWire(NodeSignal& source, NodeSocket& destination)
: source(source)
, destination(destination)
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
    connected = true;
    source.wireOutput(destination);
}

void NodeWire::disconnect()
{
    connected = false;
    source.unwireOutput(destination);
}
