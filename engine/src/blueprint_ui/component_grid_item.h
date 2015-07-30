#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "component.h"

class ComponentGridItem : public BlueprintUiObject {

public:
  explicit ComponentGridItem(ComponentProxy<EngineUiDomain>* component);

  VarSignalT<float> x = MakeVar<EngineUiDomain, float>(0);
  VarSignalT<float> y = MakeVar<EngineUiDomain, float>(0);

  ComponentProxy<EngineUiDomain>* component;

  void setPos(float x, float y);

};
