#pragma once
#include "globals.h"

#include <noise/module/perlin.h>

#include "basic_component.h"

class PerlinNoiseComponent : public BasicComponent<double> {

public:
  PerlinNoiseComponent();

  double calculate(const FrameContext& frame) const override;

  SignalFunction<double> xInput;
  SignalFunction<double> yInput;
  SignalFunction<double> zInput;

  noise::module::Perlin noiseGenerator;

};
