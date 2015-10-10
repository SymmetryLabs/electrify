template<typename Input>
ContextModifierNode<Input>::ContextModifierNode()
: contextModifierNode(make_shared<ContextModifierChain>(std::bind(
    mem_fn(&ContextModifierNode<Input>::modifyContext), this, placeholders::_1)))
{
}

template<typename Input>
void ContextModifierNode<Input>::configure(ContextModifierNode<Input>& node, NodeHandle& handle)
{
    Node::configure(node, handle);
    auto nodeSocket = make_shared<ContextModifierNodeSocket>(node, handle,
        "ContextModifierNode", node.contextModifierNode);
    handle.registerInput("ContextModifierNode", nodeSocket);
    handle.registerOutput("ContextModifierNode", nodeSocket);
}

template<typename Input>
ContextModifierNode<Input>::ContextModifierNodeSocket::ContextModifierNodeSocket(
    ContextModifierNode& node, NodeHandle& handle, const string& name,
    weak_ptr<ContextModifierChain> contextModifierNode_)
: NodeSocket(handle, name, nullptr)
, contextModifierNode(contextModifierNode_)
{
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::wireInput(weak_ptr<BaseSignal> sourceSignal)
{
    this->sourceSignal = sourceSignal;
    completeWiringIfNeeded();
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::unwireInput(weak_ptr<BaseSignal> sourceSignal)
{
    unwireIfNeeded();
    this->sourceSignal.reset();
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::wireOutput(NodeSocket& destinationNodeSocket)
{
    this->destinationNodeSocket = &destinationNodeSocket;
    completeWiringIfNeeded();
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::unwireOutput(NodeSocket& destinationNodeSocket)
{
    unwireIfNeeded();
    this->destinationNodeSocket = nullptr;
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::completeWiringIfNeeded()
{
    if (!sourceSignal.expired() && destinationNodeSocket) {
        destinationNodeSocket->wireInput(sourceSignal);
        destinationNodeSocket->registerContextModifier(contextModifierNode);
    }
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::unwireIfNeeded()
{
    if (!sourceSignal.expired() && destinationNodeSocket) {
        destinationNodeSocket->unwireInput(sourceSignal);
        destinationNodeSocket->unregisterContextModifier(contextModifierNode);
    }
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::registerContextModifier(
    weak_ptr<ContextModifierChain> contextModifier)
{
    sendCommand([] (shared_ptr<ContextModifierChain> thisContextModifier,
        shared_ptr<ContextModifierChain> nextContextModifier)
    {
        thisContextModifier->nextModifierNode = nextContextModifier.get();
    }, this->contextModifierNode, contextModifier);
}
