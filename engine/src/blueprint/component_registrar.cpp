#include "component_registrar.h"

#include "saw_wave.h"
#include "sin_wave.h"
#include "square_wave.h"
#include "scale_transform.h"
#include "color_doubler.h"
#include "constant_color_component.h"
#include "constant_component.h"
#include "hsv_component.h"
#include "incrementer.h"
#include "perlin_noise_component.h"
#include "pixel_x_component.h"
#include "time_component.h"
#include "translate_component.h"

ComponentRegistrar::ComponentRegistrar()
{
  registerComponent<SawWave>();
  registerComponent<SinWave>();
  registerComponent<SquareWave>();
  registerComponent<ScaleTransform>();
  registerComponent<ColorDoubler>();
  registerComponent<ConstantColorComponent>();
  registerComponent<ConstantFloatComponent>();
  registerComponent<HsvComponent>();
  registerComponent<Incrementer>();
  registerComponent<PerlinNoiseComponent>();
  registerComponent<PixelXComponent>();
  registerComponent<TimeComponent>();
  registerComponent<TranslateComponent>();
}

vector<string> ComponentRegistrar::getAvailableComponents() const
{
  vector<string> keys;
  keys.reserve(componentFactories.size());
  for(auto kv : componentFactories) {
      keys.push_back(kv.first);
  }
  return keys;
}
