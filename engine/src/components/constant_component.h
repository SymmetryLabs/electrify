#pragma once
#include "globals.h"

#include "basic_component.h"

template <typename V>
class ConstantComponent : public BasicComponent<V> {

public:
  ConstantComponent(V value_) : value(value_) {}

  V calculate(__attribute__((unused)) const FragmentContext& frag) const override { return value; }

private:
  V value;

};
