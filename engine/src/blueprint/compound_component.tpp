#include "component_registrar.h"

template <typename Type, typename... Targs>
Type* CompoundComponent::makeSubcomponent(Targs&&... Fargs)
{
  auto subcomponent = unique_ptr<Type>(Component::createComponent<Type>(forward<Targs>(Fargs)...));
  auto subcomponentPtr = subcomponent.get();
  addSubcomponent(move(subcomponent));
  return subcomponentPtr;
}

template <typename V>
Socket<V>* CompoundComponent::registerWirableOutput(const string& name)
{
  Socket<V>* output = new Socket<V>();
  registerOutput(name, unique_ptr<BaseSignal> {output});
  wirableOutputs[name] = output;
  return output;
}
