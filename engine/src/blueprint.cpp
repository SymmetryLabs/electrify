#include "blueprint.h"

Blueprint::Blueprint()
{
}

void Blueprint::addComponent(shared_ptr<Component> component)
{
  components.push_back(component);
}

void Blueprint::removeComponent(shared_ptr<Component> component)
{
  components.erase(std::remove(components.begin(), components.end(), component), components.end());
}
