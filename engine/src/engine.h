#pragma once
#include "constants.h"

#include "component.h"

/**
 * The engine loads networks of Components and also keeps time
 */
class Engine
{

public:
  void loadComponents(Component *root);
  void update();

};


