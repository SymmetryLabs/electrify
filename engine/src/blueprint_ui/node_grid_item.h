#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "node.h"

class NodeGridItem : public BlueprintUiObject {

public:
  explicit NodeGridItem(NodeProxy<EngineUiDomain>* node);

  VarSignalT<float> x;
  VarSignalT<float> y;
    
  EventsT<> positionChanged;

  NodeProxy<EngineUiDomain>* node;

  void setPos(float x, float y);

};
