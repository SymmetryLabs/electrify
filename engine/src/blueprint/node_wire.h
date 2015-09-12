#pragma once
#include "globals.h"

#include "node_socket.h"

class NodeWire {

public:
    NodeWire(NodeSignal& source, NodeSocket& destination);
    ~NodeWire();

    bool isConnected();
    void connect();
    void disconnect();

    NodeSignal& source;
    NodeSocket& destination;

private:

    bool connected = false;

};
