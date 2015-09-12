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

    string getName() const;

    virtual void wireOutput(NodeSocket& destinationNodeSocket);
    virtual void unwireOutput(NodeSocket& destinationNodeSocket);
 
    NodeHandle& nodeHandle;
    Var<string> name;

protected:
    BaseSignal* getSignal() const;

private:
    shared_ptr<BaseSignal> signal;

};
