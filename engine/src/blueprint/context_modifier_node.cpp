#include "context_modifier_node.h"

ContextModifierNode::ContextModifierNode(NodeHandle& nodeHandle)
: Node(nodeHandle)
, nodeSocket(make_shared<ContextModifierNodeSocket>(*this, nodeHandle, "ContextModifierNode"))
{
    nodeHandle.registerInput("ContextModifierNode", nodeSocket);
    nodeHandle.registerOutput("ContextModifierNode", nodeSocket);
}

ContextModifierNode::ContextModifierNodeSocket::ContextModifierNodeSocket(ContextModifierNode& node, NodeHandle& nodeHandle, const string& name)
: NodeSocket(nodeHandle, name, nullptr)
, contextModifierNode(std::bind(
    mem_fn(&ContextModifierNode::modifyContext), &node, placeholders::_1))
{
}

void ContextModifierNode::ContextModifierNodeSocket::wireInput(BaseSignal& sourceSignal)
{
    this->sourceSignal = &sourceSignal;
    completeWiringIfNeeded();
}

void ContextModifierNode::ContextModifierNodeSocket::unwireInput(BaseSignal& sourceSignal)
{
    unwireIfNeeded();
    this->sourceSignal = nullptr;
}

void ContextModifierNode::ContextModifierNodeSocket::wireOutput(NodeSocket& destinationNodeSocket)
{
    this->destinationNodeSocket = &destinationNodeSocket;
    completeWiringIfNeeded();
}

void ContextModifierNode::ContextModifierNodeSocket::unwireOutput(NodeSocket& destinationNodeSocket)
{
    unwireIfNeeded();
    this->destinationNodeSocket = nullptr;
}

void ContextModifierNode::ContextModifierNodeSocket::completeWiringIfNeeded()
{
    if (sourceSignal && destinationNodeSocket) {
        destinationNodeSocket->wireInput(*sourceSignal);
        destinationNodeSocket->registerContextModifier(contextModifierNode);
    }
}

void ContextModifierNode::ContextModifierNodeSocket::unwireIfNeeded()
{
    if (sourceSignal && destinationNodeSocket) {
        destinationNodeSocket->unwireInput(*sourceSignal);
        destinationNodeSocket->unregisterContextModifier(contextModifierNode);
    }
}

void ContextModifierNode::ContextModifierNodeSocket::registerContextModifier(ContextModifierChain& contextModifier)
{
    this->contextModifierNode.nextModifierNode = &contextModifier;
}
