#pragma once
#include "globals.h"

#include "basic_component.h"

template <typename V>
class ConstantComponent : public BasicComponent<V> {

public:
  ConstantComponent() {}
  explicit ConstantComponent(V value_) : value(value_) {}

  static const string componentName() { return "Constant float"; }

  V calculate(const FrameContext&) const override { return value; }

private:
  V value;

};

typedef ConstantComponent<float> ConstantFloatComponent;
