#pragma once
#include "globals.h"

#include "basic_component.h"

class TranslateComponent : BasicComponent<Color> {

public:
  TranslateComponent();

  Color calculate(const FrameContext& frame) const override;

private:
  SignalFunction<Color> signalInput;

  SignalFunction<double> translateX;
  SignalFunction<double> translateY;
  SignalFunction<double> translateZ;

};
