template <typename V>
V ValueParameter<V>::calculate(__attribute__((unused)) const FragmentContext& frag)
{
  return value;
}
