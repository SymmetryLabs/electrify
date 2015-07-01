#include "socket.h"

bool BaseSocket::acceptsSignal(const BaseSignal& signal) const
{
  return type == signal.type;
}

void BaseSocket::addContextModifier(ContextModifierChain& contextModifier)
{
  contextModifierChain = &contextModifier;
}

FrameContext ContextModifierChain::modifyContext(const FrameContext& frame)
{
  if (nextModifierNode) {
    return nextModifierNode->modifyContext(contextModifierFunction(frame));
  } else {
    return contextModifierFunction(frame);
  }
}
