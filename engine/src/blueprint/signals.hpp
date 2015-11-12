template <typename V>
V FunctionSignal<V>::calculate(const FrameContext& frame) const
{
    return calculate_function(frame);
}

template <typename V>
V ConstantSignal<V>::calculate(const FrameContext&) const
{
    return value;
}
