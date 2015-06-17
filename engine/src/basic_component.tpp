template <typename V>
BasicComponent<V>::BasicComponent()
{
  registerOutput("value", &BasicComponent::calculate);
}
