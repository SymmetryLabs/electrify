#pragma once
#include "globals.h"

#include "component.h"
#include "frame_context.h"

class ContextModifierComponent : public Component {

public:
  ContextModifierComponent()
  : contextModifierNode(bind(
      mem_fn(&ContextModifierComponent::modifyContext), this, placeholders::_1))
  {}

  virtual ~ContextModifierComponent() {}

  virtual FrameContext modifyContext(const FrameContext& original) = 0;

  void wireInput(const string& name, BaseSignal& signal) override;

  void registerContextModifier(const string& name,
    ContextModifierChain& contextModifier) override;

  void wireOutputTo(const string& emittingOutputName,
    Component& receivingSubcomponent, const string& receivingInputName) override;

  // bool canWireOutputTo(const string& emittingOutputName, const BaseSocket& receivingSocket) const override;
  void wireOutputTo(const string& emittingOutputName, BaseSocket& receivingSocket) override;

private:
  BaseSignal* sourceSignal = nullptr;
  BaseSocket* destinationSocket = nullptr;
  Component* destinationSubcomponent = nullptr;
  string destinationInputName;

  void completeWiringIfNeeded();

  ContextModifierChain contextModifierNode;

};
