#include "component.h"

void Component::registerInput(const string& name, unique_ptr<BaseSocket> inputSocket)
{
  inputs[name] = move(inputSocket);
}

BaseSocket* Component::getInput(const string& name) const
{
  try {
    return inputs.at(name).get();
  } catch (out_of_range& e) {
    return nullptr;
  }
}

bool Component::canWireInput(const string& name, const BaseSignal& signal) const
{
  auto input = getInput(name);
  return input && input->acceptsSignal(signal);
}

void Component::wireInput(const string& name, BaseSignal& signal)
{
  getInput(name)->setSignal(&signal);
}

void Component::registerContextModifier(const string& name,
  ContextModifierChain& contextModifier)
{
  getInput(name)->addContextModifier(contextModifier);
}

void Component::registerOutput(const string& name, unique_ptr<BaseSignal> signal)
{
  outputs[name] = move(signal);
}

BaseSignal* Component::getOutput(const string& name) const
{
  try {
    return outputs.at(name).get();
  } catch (out_of_range& e) {
    return nullptr;
  }
}

bool Component::canWireOutputTo(const string& emittingOutputName,
  const Component& receivingComponent, const string& receivingInputName) const
{
  auto output = getOutput(emittingOutputName);
  return output && receivingComponent.canWireInput(receivingInputName, *output);
}

bool Component::canWireOutputTo(const string& emittingOutputName,
  const BaseSocket& receivingSocket) const
{
  auto output = getOutput(emittingOutputName);
  return output && receivingSocket.acceptsSignal(*output);
}

void Component::wireOutputTo(const string& emittingOutputName,
  Component& receivingComponent, const string& receivingInputName)
{
  receivingComponent.wireInput(receivingInputName, *getOutput(emittingOutputName));
}

void Component::wireOutputTo(const string& emittingOutputName, BaseSocket& receivingSocket)
{
  receivingSocket.setSignal(getOutput(emittingOutputName));
}

void Component::registerParameter(const string& name, unique_ptr<BaseParameter> parameter)
{
  parameters[name] = move(parameter);
}
