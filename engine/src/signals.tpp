template <typename V>
V FunctionSignal<V>::calculate(const FrameContext& frame) const
{
  return calculate_function(frame);
}

template <typename V>
V ConstantSignal<V>::calculate(__attribute__((unused)) const FrameContext& frame) const
{
  return value;
}
