#pragma once
#include "globals.h"

#include "basic_component.h"

template <typename V>
class ConstantComponent : public BasicComponent<V> {

public:
  ConstantComponent() {}
  explicit ConstantComponent(V value_) : value(value_) {}

  static const string componentName() { return "Constant float"; }

  V calculate(__attribute__((unused)) const FrameContext& frame) const override { return value; }

private:
  V value;

};

typedef ConstantComponent<float> ConstantFloatComponent;
