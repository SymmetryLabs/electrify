#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"
#include "node_socket.h"

template<typename Input>
class ContextModifierNode : public Node {

public:
    virtual ~ContextModifierNode() = default;

    static void configure(ContextModifierNode<Input>& node, NodeHandle& handle);

    virtual FrameContext modifyContext(const FrameContext& original) const = 0;

private:

    struct ContextModifierNodeSocket : NodeSocket {

        ContextModifierNodeSocket(ContextModifierNode& node, NodeHandle& nodeHandle, const string& name);

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

#include "context_modifier_node.hpp"
