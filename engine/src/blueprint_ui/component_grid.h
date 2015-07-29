#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "compound_component.h"
#include "component_grid_item.h"
#include "observable_vector.h"
#include "component.h"
#include "observes.h"

class ComponentGrid : public BlueprintUiObject, Observes<EngineUiDomain> {

public:
  explicit ComponentGrid(CompoundComponentProxy<EngineUiDomain>* compoundComponent);

  void addComponent(string name, float x, float y);
  void removeComponent();

  ObservableVector<EngineUiDomain, shared_ptr<ComponentGridItem>> gridItems;

private:
  CompoundComponentProxy<EngineUiDomain>* compoundComponent;

  ComponentGridItem* addGridItemWith(size_t pos, ComponentProxy<EngineUiDomain>& component);
  shared_ptr<ComponentGridItem> removeGridItemWith(size_t pos, ComponentProxy<EngineUiDomain>& component);

};
