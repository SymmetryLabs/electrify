#include "compound_component.h"

CompoundComponent::CompoundComponent()
{
  registerOutput("color", &CompoundComponent::calculate_color);
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

Color CompoundComponent::calculate_color(const FragmentContext& frag)
{
  return Color(255);
}

void CompoundComponent::addSubcomponent(unique_ptr<Component> subcomponent)
{
  subcomponents.push_back(move(subcomponent));
}

void CompoundComponent::removeSubcomponent(const unique_ptr<Component>& subcomponent)
{
  subcomponents.erase(remove(subcomponents.begin(), subcomponents.end(), subcomponent), subcomponents.end());
}
