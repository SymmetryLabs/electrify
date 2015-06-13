template <typename V>
Socket<V>* CompoundComponent::registerWirableOutput(const string& name)
{
  Socket<V>* output = new Socket<V>();
  registerOutput(name, unique_ptr<BaseSignal> {output});
  wirableOutputs[name] = output;
  return output;
}

template <typename V>
Socket<V>* CompoundComponent::getWirableOutput(const string& name) {
  return (Socket<V>*)wirableOutputs[name];
}

template <typename V>
void CompoundComponent::wireOutput(const string& name, Signal<V>* signal) {
  getWirableOutput<V>(name)->setSignal(signal);
}
