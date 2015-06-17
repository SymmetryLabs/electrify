template <typename V>
void Socket<V>::setSignal(Signal<V>* signal_)
{
  signal = signal_;
}

template <typename V>
bool Socket<V>::hasSignal()
{
  return signal;
}

template <typename V>
V Socket<V>::calculate(const FragmentContext& frag) const
{
  return signal ? signal->calculate(frag) : defaultValue.calculate(frag);
}

template <typename V>
void ProxySocket<V>::setSignal(Signal<V>* signal)
{
  Socket<V>::setSignal(signal);
  if (signalAddr) {
    *signalAddr = signal;
  }
  if (signalFunctionAddr) {
    *signalFunctionAddr = SignalFunction<V>(signal ? signal : &this->defaultValue);
  }
}
