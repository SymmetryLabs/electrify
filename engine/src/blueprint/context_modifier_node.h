#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"
#include "node_socket.h"

template<typename Input>
class ContextModifierNode : public Node {

public:
    ContextModifierNode();
    virtual ~ContextModifierNode() = default;

    static void configure(ContextModifierNode<Input>& node, NodeHandle& handle);

    virtual FrameContext modifyContext(const FrameContext& original) const = 0;

private:
    shared_ptr<ContextModifierChain> contextModifierNode;

    struct ContextModifierNodeSocket : NodeSocket {

        ContextModifierNodeSocket(ContextModifierNode& node, NodeHandle& nodeHandle, const string& name, weak_ptr<ContextModifierChain> contextModifierNode);

        void wireInput(weak_ptr<BaseSignal> sourceSignal) override;
        void unwireInput(weak_ptr<BaseSignal> sourceSignal) override;

        void wireOutput(NodeSocket& destinationNodeSocket) override;
        void unwireOutput(NodeSocket& destinationNodeSocket) override;

        void completeWiringIfNeeded();
        void unwireIfNeeded();

        void registerContextModifier(weak_ptr<ContextModifierChain> contextModifier) override;

        weak_ptr<BaseSignal> sourceSignal;
        NodeSocket* destinationNodeSocket = nullptr;

        weak_ptr<ContextModifierChain> contextModifierNode;

    };

    NODE_IMPL_ABSTRACT();

};

#include "context_modifier_node.hpp"
