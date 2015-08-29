template <typename V>
void Node::registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue) {
    registerInput(name, make_unique<ProxySocket<V>>(inputAddr, defaultValue));
}

template <typename V, typename C>
void Node::registerOutput(const string& name, V (C::* calculate_function_)(const FrameContext& frame) const) {
    outputs.push_back(make_shared<NodeSignal>(*this, name, make_unique<FunctionSignal<V>>(calculate_function_, this)));
}

// template<class Archive>
// void Node::serialize(Archive& archive)
// {

// }
