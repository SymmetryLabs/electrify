template<typename ClassType>
void ComponentRegistrar::registerComponent()
{
  componentFactories[ClassType::componentName()] = []() -> ClassType* {
    return Component::createComponent<ClassType>();
  };
}

template<typename ClassType>
unique_ptr<ClassType> ComponentRegistrar::getComponent(const string& name) const
{
  return unique_ptr<ClassType>(dynamic_cast<ClassType*>(componentFactories.at(name)()));
}
