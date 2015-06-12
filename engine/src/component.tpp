template <class V, class C>
void Component::registerOutput(const string& name, V (C::* calculate_function_)(const FragmentContext& frag)) {
  Signal<V>* signal = new Signal<V>(calculate_function_, this);
  outputs[name] = move(unique_ptr<BaseSignal>(signal));
}

template <class V>
Signal<V>* Component::getOutput(const string& name) {
  return (Signal<V>*)outputs[name].get();
}

template <class V>
Socket<V>* Component::getInput(const string& name) {
  return (Socket<V>*)inputs[name].get();
}

template <class V>
void Component::wireInput(const string& name, Signal<V>* signal) {
  getInput<V>(name)->signal = signal;
}
