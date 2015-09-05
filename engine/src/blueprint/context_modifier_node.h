#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"
#include "node_socket.h"

class ContextModifierNode : public Node {

public:
    explicit ContextModifierNode(const string& name);
    virtual ~ContextModifierNode() = default;

    virtual FrameContext modifyContext(const FrameContext& original) const = 0;

private:

    struct ContextModifierNodeSocket : public NodeSocket {

        ContextModifierNodeSocket(ContextModifierNode& node, const string& name);

        void wireInput(BaseSignal& sourceSignal) override;
        void unwireInput(BaseSignal& sourceSignal) override;

        void wireOutput(NodeSocket& destinationNodeSocket) override;
        void unwireOutput(NodeSocket& destinationNodeSocket) override;

        void completeWiringIfNeeded();
        void unwireIfNeeded();

        void registerContextModifier(ContextModifierChain& contextModifier) override;

        BaseSignal* sourceSignal = nullptr;
        NodeSocket* destinationNodeSocket = nullptr;

        ContextModifierChain contextModifierNode;

    };

    shared_ptr<ContextModifierNodeSocket> nodeSocket;

};
