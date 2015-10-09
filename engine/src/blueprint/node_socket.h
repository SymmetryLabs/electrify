#pragma once
#include "globals.h"

#include "node_signal.h"

class NodeHandle;
class NodeSocket;
class BaseSocket;
class BaseSignal;
class ContextModifierChain;

class NodeSocket : public NodeSignal {

public:
    NodeSocket(NodeHandle& nodeHandle, const string& name, const shared_ptr<BaseSocket>& socket);
    virtual ~NodeSocket() = default;

    virtual void wireInput(weak_ptr<BaseSignal> sourceSignal);
    virtual void unwireInput(weak_ptr<BaseSignal> sourceSignal);

    virtual void registerContextModifier(ContextModifierChain& contextModifier);
    virtual void unregisterContextModifier(ContextModifierChain& contextModifier);

private:
    ENABLE_TYPE_ERASURE();

};
