#include "context_modifier_component.h"

void ContextModifierComponent::wireInput(const string& name, BaseSignal& signal)
{
  sourceSignal = &signal;
  completeWiringIfNeeded();
}

void ContextModifierComponent::registerContextModifier(const string& name,
  ContextModifierChain& contextModifier)
{
  contextModifierNode.nextModifierNode = &contextModifier;
}

void ContextModifierComponent::wireOutputTo(const string& emittingOutputName,
  Component& receivingSubcomponent, const string& receivingInputName)
{
  destinationSubcomponent = &receivingSubcomponent;
  destinationInputName = receivingInputName;
  completeWiringIfNeeded();
}

void ContextModifierComponent::wireOutputTo(const string& emittingOutputName,
  BaseSocket& receivingSocket)
{
  destinationSocket = &receivingSocket;
  completeWiringIfNeeded();
}

void ContextModifierComponent::completeWiringIfNeeded()
{
  if (sourceSignal && destinationSubcomponent) {
    destinationSubcomponent->wireInput(destinationInputName, *sourceSignal);
    destinationSubcomponent->registerContextModifier(destinationInputName, contextModifierNode);
  } else if (sourceSignal && destinationSocket) {
    destinationSocket->setSignal(sourceSignal);
    destinationSocket->addContextModifier(contextModifierNode);
  }
}
