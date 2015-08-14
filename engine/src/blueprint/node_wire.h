#pragma once
#include "globals.h"

#include "node_socket.h"

class NodeWire {

public:
    NodeWire(NodeSocket& emittingSocket, NodeSocket& receivingSocket)
    : emittingSocket(emittingSocket)
    , receivingSocket(receivingSocket)
    {
    }

    NodeSocket emittingSocket;
    NodeSocket receivingSocket;

};
