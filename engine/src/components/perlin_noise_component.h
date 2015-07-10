#pragma once
#include "globals.h"

#include <noise/module/perlin.h>

#include "basic_component.h"

class PerlinNoiseComponent : public BasicComponent<float> {

public:
  PerlinNoiseComponent();

  static const string componentName() { return "Perlin noise"; }

  float calculate(const FrameContext& frame) const override;

  SignalFunction<float> xInput;
  SignalFunction<float> yInput;
  SignalFunction<float> zInput;

  noise::module::Perlin noiseGenerator;

};
