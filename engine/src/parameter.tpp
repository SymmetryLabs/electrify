template <typename V>
V ValueParameter<V>::calculate(__attribute__((unused)) const FrameContext& frame)
{
  return value;
}
