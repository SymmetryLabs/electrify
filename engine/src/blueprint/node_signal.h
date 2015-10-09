#pragma once
#include "globals.h"

#include "var.h"
#include "data_transmitter.h"

class NodeHandle;
class NodeSocket;
class BaseSignal;

class NodeSignal : public DataTransmitter {

public:
    NodeSignal(NodeHandle& nodeHandle, const string& name, const shared_ptr<BaseSignal>& signal);
    virtual ~NodeSignal();

    NodeHandle& getNodeHandle() const;

    string getName() const;

    virtual void wireOutput(NodeSocket& destinationNodeSocket);
    virtual void unwireOutput(NodeSocket& destinationNodeSocket);

    bool belongsTo(const NodeHandle& nodeHandle) const;
 
    Var<string> name;

protected:
    BaseSignal* getSignal() const;

private:
    shared_ptr<BaseSignal> signal;
    weak_ptr<NodeHandle> nodeHandle;

    ENABLE_TYPE_ERASURE();

};
