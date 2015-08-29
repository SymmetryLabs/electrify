#include "socket.h"

BaseSocket::operator BaseSignal() const
{
    return static_cast<BaseSignal>(*this);
}

bool BaseSocket::acceptsSignal(const BaseSignal& signal) const
{
    return type == signal.type;
}

void BaseSocket::addContextModifier(ContextModifierChain& contextModifier)
{
    contextModifierChain = &contextModifier;
}

void BaseSocket::removeContextModifier(ContextModifierChain& contextModifier)
{
    contextModifierChain = nullptr;
}

FrameContext ContextModifierChain::modifyContext(const FrameContext& frame)
{
    if (nextModifierNode) {
        return nextModifierNode->modifyContext(contextModifierFunction(frame));
    } else {
        return contextModifierFunction(frame);
    }
}
