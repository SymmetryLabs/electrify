#include "compound_component.h"

#include <algorithm>

CompoundComponent::CompoundComponent()
{
}

void CompoundComponent::init()
{
  for (auto& subcomponent : subcomponents) {
    subcomponent->init();
  }
}

void CompoundComponent::update(const FrameContext& frame)
{
  for (auto& subcomponent : subcomponents) {
    subcomponent->update(frame);
  }
}

bool CompoundComponent::isFullyWired()
{
  return Component::isFullyWired()
    && all_of(subcomponents.begin(), subcomponents.end(),
      [](const unique_ptr<Component>& comp) -> bool {
        return comp->isFullyWired();
      })
    && all_of(wirableOutputs.begin(), wirableOutputs.end(),
      [](unordered_map<string, BaseSocket*>::value_type& pair) -> bool {
        return pair.second->hasSignal();
      });
}

void CompoundComponent::addSubcomponent(unique_ptr<Component> subcomponent)
{
  subcomponents.push_back(move(subcomponent));
}

void CompoundComponent::removeSubcomponent(const unique_ptr<Component>& subcomponent)
{
  // TODO: break connections
  subcomponents.erase(remove(subcomponents.begin(), subcomponents.end(), subcomponent), subcomponents.end());
}

void wireSubcomponents(Component& emittingSubcomponent, string& emittingOutputName,
  Component& receivingSubcomponent, string& receivingInputName)
{

}
