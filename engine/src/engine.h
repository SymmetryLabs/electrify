#pragma once
#include "constants.h"

#include "component.h"
#include "blueprint.h"

/**
 * The engine loads networks of Components and also keeps time
 */
class Engine {

public:
  Engine(shared_ptr<Blueprint> blueprint_);
  virtual ~Engine() {}

  void start();
  void stop();

private:
  shared_ptr<Blueprint> blueprint;

};
