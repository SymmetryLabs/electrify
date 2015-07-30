#include "component_grid.h"

ComponentGrid::ComponentGrid(CompoundComponentProxy<EngineUiDomain>* compoundComponent_)
  : compoundComponent(compoundComponent_)
{
  addObserver(Observe(compoundComponent->subcomponents.valueAdded, [this] (const pair<size_t, shared_ptr<ComponentProxy<EngineUiDomain>>>& pair) {
    addGridItemWith(pair.first, *pair.second.get());
  }));
  addObserver(Observe(compoundComponent->subcomponents.valueRemoved, [this] (const pair<size_t, shared_ptr<ComponentProxy<EngineUiDomain>>>& pair) {
    removeGridItemWith(pair.first, *pair.second.get());
  }));
  size_t i = 0;
  for (auto& component : compoundComponent->subcomponents) {
    addGridItemWith(i++, *component);
  }
}

void ComponentGrid::addComponent(string name, float x, float y)
{
  compoundComponent->addSubcomponent(name, [=] (size_t pos) {
    gridItems[pos]->setPos(x, y);
  });
}

void ComponentGrid::removeComponent()
{
}

ComponentGridItem* ComponentGrid::addGridItemWith(size_t pos, ComponentProxy<EngineUiDomain>& component)
{
  vector<shared_ptr<ComponentGridItem>>::iterator iter = gridItems.begin() + pos;
  gridItems.insert(iter, make_shared<ComponentGridItem>(&component));
  return gridItems.back().get();
}

shared_ptr<ComponentGridItem> ComponentGrid::removeGridItemWith(size_t pos, ComponentProxy<EngineUiDomain>& component)
{
  auto gridItem = move(gridItems[pos]);
  gridItems.erase(gridItems.begin() + pos);
  return gridItem;
}
