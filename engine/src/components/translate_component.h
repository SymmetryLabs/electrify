#pragma once
#include "globals.h"

#include "basic_component.h"

class TranslateComponent : BasicComponent<void*> {

public:
  TranslateComponent();

  void* calculate(const FrameContext& frame) const override;

private:
  SignalFunction<void*> signalInput;

  SignalFunction<double> translateX;
  SignalFunction<double> translateY;
  SignalFunction<double> translateZ;

};
