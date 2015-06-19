template <typename V>
void Component::registerInput(const string& name, Signal<V>** inputAddr) {
  registerInput(name, make_unique<ProxySocket<V>>(inputAddr));
}

template <typename V>
void Component::registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue) {
  registerInput(name, make_unique<ProxySocket<V>>(inputAddr, defaultValue));
}

template <typename V>
Socket<V>* Component::getInput(const string& name) const {
  return (Socket<V>*)inputs.at(name).get();
}

template <typename V>
void Component::wireInput(const string& name, Signal<V>* signal) {
  getInput<V>(name)->setSignal(signal);
}

template <typename V, typename C>
void Component::registerOutput(const string& name, V (C::* calculate_function_)(const FragmentContext& frag) const) {
  outputs[name] = make_unique<FunctionSignal<V>>(calculate_function_, this);
}

template <typename V>
Signal<V>* Component::getOutput(const string& name) const {
  return (Signal<V>*)outputs.at(name).get();
}
