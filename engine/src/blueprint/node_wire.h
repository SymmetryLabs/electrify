#pragma once
#include "globals.h"

#include "node_socket.h"
#include "data_proxy.h"
#include "proxyable.h"

class NodeWireProxy;

class NodeWire : public Proxyable {

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

    SYNTHESIZE_PROXYABLE(NodeWireProxy);

};

class NodeWireProxy : public DataProxy {

public:
    NodeWireProxy(shared_ptr<NodeWire> master, ProxyBridge& proxyBridge)
        : DataProxy(master, proxyBridge)
    {
        this->source = master->source.getProxy<NodeSignalProxy>(proxyBridge);
        this->destination = master->destination.getProxy<NodeSocketProxy>(proxyBridge);
    }

    shared_ptr<NodeSignalProxy> source;
    shared_ptr<NodeSocketProxy> destination;
};
