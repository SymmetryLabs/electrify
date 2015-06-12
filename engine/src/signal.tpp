template <class V>
V Signal<V>::calculate(const FragmentContext& frag)
{
  return calculate_function(frag);
}

template <class V>
V Socket<V>::calculate(const FragmentContext& frag) {
  return signal->calculate(frag);
}
