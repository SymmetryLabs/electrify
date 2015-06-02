#ifndef ENGINE_H
#define ENGINE_H

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


#endif // ENGINE_H