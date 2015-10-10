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

    bool isConnected() const;
    void connect();
    void disconnect();

    NodeSignal* getSource() const;
    NodeSocket* getDestination() const;

    bool isAssignedTo(const NodeHandle& nodeHandle) const;

private:
    NodeSignal* source = nullptr;
    NodeSocket* destination = nullptr;

    weak_ptr<NodeHandle> sourceHandle;
    string sourceName;
    weak_ptr<NodeHandle> destinationHandle;
    string destinationName;

    bool connected = false;

    void populateSignals();

    template <typename Archive>
    friend void save(Archive& archive, const NodeWire& nodeWire);
    template <typename Archive>
    friend void load(Archive& archive, NodeWire& nodeWire);

};
