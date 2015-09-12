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

    virtual void wireInput(BaseSignal& sourceSignal);
    virtual void unwireInput(BaseSignal& sourceSignal);

    virtual void registerContextModifier(ContextModifierChain& contextModifier);
    virtual void unregisterContextModifier(ContextModifierChain& contextModifier);

protected:
    BaseSocket* getSocket() const;

};
