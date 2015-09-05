#pragma once
#include "globals.h"

#include "data_proxy.h"
#include "proxyable.h"
#include "signals.h"

class Node;
class NodeProxy;
class NodeSignalProxy;
class NodeSocket;

class NodeSignal : public Proxyable {

public:
    NodeSignal(Node& node, const string& name, unique_ptr<BaseSignal>&& signal);
    virtual ~NodeSignal() = default;

    string getName() const;

    virtual void wireOutput(NodeSocket& destinationNodeSocket);
    virtual void unwireOutput(NodeSocket& destinationNodeSocket);
 
    Node& node;
    Var<string> name;

    unique_ptr<BaseSignal> signal;

protected:
    virtual BaseSignal* getSignal() const;

private:

    SYNTHESIZE_PROXYABLE(NodeSignalProxy);

};

class NodeSignalProxy : public DataProxy {

public:
    NodeSignalProxy(shared_ptr<NodeSignal> master, ProxyBridge& proxyBridge);
    virtual ~NodeSignalProxy() {}
    void init(shared_ptr<NodeSignal> master, ProxyBridge& proxyBridge);
    
    shared_ptr<NodeProxy> node;
    Var<string> name;
    
};
