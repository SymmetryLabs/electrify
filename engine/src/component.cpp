#include "component.h"

#include <algorithm>

bool Component::isFullyWired()
{
  return all_of(inputs.begin(), inputs.end(), [](unordered_map<string, unique_ptr<BaseSocket>>::value_type& pair) -> bool {
    return pair.second->hasSignal();
  });
}

void Component::registerInput(const string& name, unique_ptr<BaseSocket> inputSocket)
{
  inputs[name] = move(inputSocket);
}

void Component::registerOutput(const string& name, unique_ptr<BaseSignal> signal)
{
  outputs[name] = move(signal);
}

void Component::registerParameter(const string& name, unique_ptr<BaseParameter> parameter)
{
  parameters[name] = move(parameter);
}
