#include "context_modifier_node.h"

void ContextModifierNode::wireInput(const string& name, BaseSignal& signal)
{
    sourceSignal = &signal;
    completeWiringIfNeeded();
}

void ContextModifierNode::registerContextModifier(const string& name,
    ContextModifierChain& contextModifier)
{
    contextModifierNode.nextModifierNode = &contextModifier;
}

void ContextModifierNode::wireOutputTo(const string& emittingOutputName,
    Node& receivingSubnode, const string& receivingInputName)
{
    destinationSubnode = &receivingSubnode;
    destinationInputName = receivingInputName;
    completeWiringIfNeeded();
}

void ContextModifierNode::wireOutputTo(const string& emittingOutputName,
    BaseSocket& receivingSocket)
{
    destinationSocket = &receivingSocket;
    completeWiringIfNeeded();
}

void ContextModifierNode::completeWiringIfNeeded()
{
    if (sourceSignal && destinationSubnode) {
        destinationSubnode->wireInput(destinationInputName, *sourceSignal);
        destinationSubnode->registerContextModifier(destinationInputName, contextModifierNode);
    } else if (sourceSignal && destinationSocket) {
        destinationSocket->setSignal(sourceSignal);
        destinationSocket->addContextModifier(contextModifierNode);
    }
}
