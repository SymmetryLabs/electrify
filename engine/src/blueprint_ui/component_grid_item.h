#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "component.h"

class ComponentGridItem : public BlueprintUiObject {

public:
  explicit ComponentGridItem(ComponentProxy<EngineUiDomain>* component);

  float x;
  float y;

  ComponentProxy<EngineUiDomain>* component;

};
