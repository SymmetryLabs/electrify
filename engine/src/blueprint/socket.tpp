template <typename V>
void Socket<V>::setSignal(BaseSignal* signal)
{
    setSignal((SignalX<V>*)signal);
}

template <typename V>
void Socket<V>::setSignal(SignalX<V>* signal_)
{
    signal = signal_;
}

template <typename V>
bool Socket<V>::hasSignal() const
{
    return signal;
}

template <typename V>
V Socket<V>::calculate(const FrameContext& frame) const
{
    if (contextModifierChain) {
        auto newFrame = contextModifierChain->modifyContext(frame);
        return signal ? signal->calculate(newFrame) : defaultValue.calculate(newFrame);
    } else {
        return signal ? signal->calculate(frame) : defaultValue.calculate(frame);
    }
}

template <typename V>
void ProxySocket<V>::setSignal(SignalX<V>* signal)
{
    Socket<V>::setSignal(signal);
    if (signalAddr) {
        *signalAddr = signal;
    }
    if (signalFunctionAddr) {
        *signalFunctionAddr = SignalFunction<V>(signal ? signal : &this->defaultValue);
    }
}
