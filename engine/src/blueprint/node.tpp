template <typename V>
void Node::registerInput(const string& name, SignalX<V>** inputAddr) {
    registerInput(name, make_unique<ProxySocket<V>>(inputAddr));
}

template <typename V>
void Node::registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue) {
    registerInput(name, make_unique<ProxySocket<V>>(inputAddr, defaultValue));
}

template <typename V, typename C>
void Node::registerOutput(const string& name, V (C::* calculate_function_)(const FrameContext& frame) const) {
    outputs[name] = make_unique<FunctionSignal<V>>(calculate_function_, this);
}

template <typename V>
SignalX<V>* Node::getOutput(const string& name) const {
    return (SignalX<V>*)getOutput(name);
}

template<class Archive>
void Node::serialize(Archive& archive)
{

}
