#pragma once
#include "globals.h"

class NodeSignal;
class NodeSocket;
class NodeHandle;

class NodeWire {

public:
    NodeWire() = default;
    NodeWire(NodeSignal& source, NodeSocket& destination);
    ~NodeWire();

    bool isConnected();
    void connect();
    void disconnect();

    NodeSignal* getSource() const;
    NodeSocket* getDestination() const;

    bool isAssignedTo(const NodeHandle& nodeHandle) const;

private:
    weak_ptr<NodeSignal> source;
    weak_ptr<NodeSocket> destination;

    bool connected = false;

    template <typename Archive>
    friend void serialize(Archive& archive, NodeWire& nodeWire);

};
