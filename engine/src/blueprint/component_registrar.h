#pragma once
#include "globals.h"

#include "component.h"

class ComponentRegistrar {

public:
  ComponentRegistrar();

  template<typename ClassType>
  void registerComponent(const string& name);

  vector<string> getAvailableComponents();

  template<typename ClassType = Component>
  unique_ptr<ClassType> getComponent(const string& name);

private:
  unordered_map<string, function<Component* ()>> componentFactories;

};

#include "component_registrar.tpp"
