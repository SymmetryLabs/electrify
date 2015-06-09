#pragma once
#include "constants.h"

#include "component.h"
#include "Signal.h"

class Blueprint {

public:
  Blueprint();
  virtual ~Blueprint() {}

  void addComponent(shared_ptr<Component> component);
  void removeComponent(shared_ptr<Component> component);

  vector<shared_ptr<Component>> components;
  InputSocket<Color> outputSocket;

};
