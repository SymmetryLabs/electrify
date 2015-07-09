template<typename ClassType>
void ComponentRegistrar::registerComponent(const string& name)
{
  componentFactories[name] = []() -> ClassType* {
    return new ClassType();
  };
}

template<typename ClassType>
unique_ptr<ClassType> ComponentRegistrar::getComponent(const string& name)
{
  return unique_ptr<ClassType>(dynamic_cast<ClassType*>(componentFactories.at(name)()));
}
