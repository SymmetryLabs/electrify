#pragma once
#include "globals.h"

#include "component.h"

class ComponentRegistrar {

public:
  ComponentRegistrar();

  template<typename ClassType>
  void registerComponent();

  vector<string> getAvailableComponents() const;

  template<typename ClassType = Component>
  unique_ptr<ClassType> getComponent(const string& name) const;

private:
  unordered_map<string, function<Component* ()>> componentFactories;

};

#include "component_registrar.tpp"
