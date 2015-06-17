#pragma once
#include "constants.h"

#include "component.h"

class HsvComponent : public Component {

public:
  SignalFunction<double> hue;
  SignalFunction<double> saturation;
  SignalFunction<double> value;

};
