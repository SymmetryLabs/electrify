#pragma once
#include "globals.h"

#include <boost/uuid/uuid.hpp>

#include "data_proxy.h"
#include "proxyable.h"
#include "signals.h"
#include "socket.h"
#include "node_signal.h"

class NodeSocketProxy;

class NodeSocket : public NodeSignal, public Proxyable {

public:
    NodeSocket(Node& node, const string& name, unique_ptr<BaseSocket>&& socket);
    virtual ~NodeSocket() = default;

    virtual void wireInput(BaseSignal& sourceSignal);
    virtual void unwireInput(BaseSignal& sourceSignal);

    virtual void registerContextModifier(ContextModifierChain& contextModifier);
    virtual void unregisterContextModifier(ContextModifierChain& contextModifier);

protected:
    virtual BaseSignal* getSignal() const override;

private:

    unique_ptr<BaseSocket> socket;

    SYNTHESIZE_PROXYABLE(NodeSocketProxy);

};

class NodeSocketProxy : public NodeSignalProxy {

public:
    NodeSocketProxy(shared_ptr<NodeSocket> master, ProxyBridge& proxyBridge);
};
