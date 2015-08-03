#pragma once
#include "globals.h"

#include "node.h"
#include "frame_context.h"

class ContextModifierNode : public Node {

public:
  ContextModifierNode()
  : contextModifierNode(bind(
      mem_fn(&ContextModifierNode::modifyContext), this, placeholders::_1))
  {}

  virtual ~ContextModifierNode() {}

  virtual FrameContext modifyContext(const FrameContext& original) = 0;

  void wireInput(const string& name, BaseSignal& signal) override;

  void registerContextModifier(const string& name,
    ContextModifierChain& contextModifier) override;

  void wireOutputTo(const string& emittingOutputName,
    Node& receivingSubnode, const string& receivingInputName) override;

  // bool canWireOutputTo(const string& emittingOutputName, const BaseSocket& receivingSocket) const override;
  void wireOutputTo(const string& emittingOutputName, BaseSocket& receivingSocket) override;

private:
  BaseSignal* sourceSignal = nullptr;
  BaseSocket* destinationSocket = nullptr;
  Node* destinationSubnode = nullptr;
  string destinationInputName;

  void completeWiringIfNeeded();

  ContextModifierChain contextModifierNode;

};
