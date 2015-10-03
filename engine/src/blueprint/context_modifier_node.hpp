template<typename Input>
void ContextModifierNode<Input>::configure(ContextModifierNode<Input>& node, NodeHandle& handle)
{
    Node::configure(node, handle);
    node.nodeSocket = make_shared<ContextModifierNodeSocket>(node, handle, "ContextModifierNode");
    handle.registerInput("ContextModifierNode", node.nodeSocket);
    handle.registerOutput("ContextModifierNode", node.nodeSocket);
}

template<typename Input>
ContextModifierNode<Input>::ContextModifierNodeSocket::ContextModifierNodeSocket(ContextModifierNode& node, NodeHandle& handle, const string& name)
: NodeSocket(handle, name, nullptr)
, contextModifierNode(std::bind(
    mem_fn(&ContextModifierNode<Input>::modifyContext), &node, placeholders::_1))
{
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::wireInput(BaseSignal& sourceSignal)
{
    this->sourceSignal = &sourceSignal;
    completeWiringIfNeeded();
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::unwireInput(BaseSignal& sourceSignal)
{
    unwireIfNeeded();
    this->sourceSignal = nullptr;
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
    if (sourceSignal && destinationNodeSocket) {
        destinationNodeSocket->wireInput(*sourceSignal);
        destinationNodeSocket->registerContextModifier(contextModifierNode);
    }
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::unwireIfNeeded()
{
    if (sourceSignal && destinationNodeSocket) {
        destinationNodeSocket->unwireInput(*sourceSignal);
        destinationNodeSocket->unregisterContextModifier(contextModifierNode);
    }
}

template<typename Input>
void ContextModifierNode<Input>::ContextModifierNodeSocket::registerContextModifier(ContextModifierChain& contextModifier)
{
    this->contextModifierNode.nextModifierNode = &contextModifier;
}
