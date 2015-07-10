#pragma once
#include "globals.h"

#include "basic_component.h"

class HsvComponent : public BasicComponent<Color> {

public:
  HsvComponent();

  static const string componentName() { return "HSV"; }

  Color calculate(const FrameContext& frame) const override;
  
  SignalFunction<float> hue;
  SignalFunction<float> saturation;
  SignalFunction<float> value;

};
