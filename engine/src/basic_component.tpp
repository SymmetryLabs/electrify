template <typename V>
BasicComponent<V>::BasicComponent()
{
  registerOutput("primary", &BasicComponent::calculate);
}
