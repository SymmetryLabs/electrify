#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "node.h"

class NodeGridItem : public BlueprintUiObject {

public:
  explicit NodeGridItem(NodeProxy<EngineUiDomain>* node);

  VarSignalT<float> x = MakeVar<EngineUiDomain, float>(0);
  VarSignalT<float> y = MakeVar<EngineUiDomain, float>(0);

  NodeProxy<EngineUiDomain>* node;

  void setPos(float x, float y);

};
