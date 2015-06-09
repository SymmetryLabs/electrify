#pragma once
#include "constants.h"

#include "component.h"

class Blueprint {

public:
  Blueprint();
  virtual ~Blueprint() {}

  void addComponent(shared_ptr<Component> component);
  void removeComponent(shared_ptr<Component> component);

  shared_ptr<Component> rootComponent;
  vector<shared_ptr<Component>> components;

};
