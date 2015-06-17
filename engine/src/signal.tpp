template <typename V>
V FunctionSignal<V>::calculate(const FragmentContext& frag) const
{
  return calculate_function(frag);
}

template <typename V>
V ConstantSignal<V>::calculate(__attribute__((unused)) const FragmentContext& frag) const
{
  return value;
}
