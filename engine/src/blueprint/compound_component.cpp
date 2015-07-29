#include "compound_component.h"

void CompoundComponent::init()
{
  for (auto& subcomponent : subcomponents) {
    subcomponent->init();
  }
}

void CompoundComponent::deinit()
{
  for (auto& subcomponent : subcomponents) {
    subcomponent->deinit();
  }
}

void CompoundComponent::update(const FrameContext& frame)
{
  for (auto& subcomponent : subcomponents) {
    subcomponent->update(frame);
  }
}

Component* CompoundComponent::createSubcomponent(const string& name)
{
  ComponentRegistrar registrar;
  auto subcomponent = registrar.getComponent(name);
  auto subcomponentPtr = subcomponent.get();
  addSubcomponent(move(subcomponent));
  return subcomponentPtr;
}

void CompoundComponent::addSubcomponent(unique_ptr<Component> subcomponent)
{
  subcomponents.push_back(move(subcomponent));
}

void CompoundComponent::removeSubcomponent(Component* subcomponent)
{
  // TODO: break connections
  removeSharedPtr(subcomponents, subcomponent);
}

bool CompoundComponent::canWireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
  Component& receivingSubcomponent, const string& receivingInputName)
{
  return emittingSubcomponent.canWireOutputTo(emittingOutputName, receivingSubcomponent, receivingInputName);
}

void CompoundComponent::wireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
  Component& receivingSubcomponent, const string& receivingInputName)
{
  return emittingSubcomponent.wireOutputTo(emittingOutputName, receivingSubcomponent, receivingInputName);
}

void CompoundComponent::unwireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
  Component& receivingSubcomponent, const string& receivingInputName)
{
  // TODO
}

BaseSocket* CompoundComponent::getWirableOutput(const string& name)
{
  try {
    return wirableOutputs.at(name);
  } catch (out_of_range& e) {
    return nullptr;
  }
}

void CompoundComponent::wireOutput(const string& name,
  Component& emittingSubcomponent, const string& emittingOutputName)
{
  emittingSubcomponent.wireOutputTo(emittingOutputName, *getWirableOutput(name));
}
