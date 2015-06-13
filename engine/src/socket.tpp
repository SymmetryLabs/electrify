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
V Socket<V>::calculate(const FragmentContext& frag)
{
  return signal->calculate(frag);
}

template <typename V>
void ProxySocket<V>::setSignal(Signal<V>* signal_)
{
  Socket<V>::setSignal(signal_);
  *signalAddr = signal_;
}
