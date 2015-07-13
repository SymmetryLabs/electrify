template <typename V>
BasicComponent<V>::BasicComponent()
{
  registerOutput("output", &BasicComponent::calculate);
}
