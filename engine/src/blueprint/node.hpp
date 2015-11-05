template<typename V>
shared_ptr<BaseSocket> Node::generateInput(SignalFunction<V>* inputAddr,
    const V defaultValue)
{
    auto socket = make_shared<ProxySocket<V>>(inputAddr, defaultValue);
    inputs.push_back(socket);
    return socket;
}

template<typename V, typename C>
shared_ptr<BaseSignal> Node::generateOutput(
    V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst)
{
    auto signal = make_shared<FunctionSignal<V>>(calculate_function_, inst);
    outputs.push_back(signal);
    return signal;
}
