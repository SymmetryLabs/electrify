#pragma once
#include "globals.h"

#include "basic_component.h"

class HsvComponent : public BasicComponent<Color> {

public:
  HsvComponent();

  Color calculate(const FragmentContext& frag) const override;
  
  SignalFunction<double> hue;
  SignalFunction<double> saturation;
  SignalFunction<double> value;

};
