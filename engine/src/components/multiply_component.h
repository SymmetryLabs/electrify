#pragma once
#include "globals.h"

#include "basic_component.h"

class MultiplyComponent : public BasicComponent<double> {

public:
  MultiplyComponent();

  double calculate(const FrameContext& frame) const override;

  SignalFunction<double> signalInput;
  SignalFunction<double> multiplyAmount;

};
