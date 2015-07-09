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
  registerComponent<SawWave>("Sawtooth wave");
  registerComponent<SinWave>("Sin wave");
  registerComponent<SquareWave>("Square wave");
  registerComponent<ScaleTransform>("Scale");
  registerComponent<ColorDoubler>("Color doubler");
  registerComponent<ConstantColorComponent>("Constant color");
  registerComponent<ConstantFloatComponent>("Constant float");
  registerComponent<HsvComponent>("HSV");
  registerComponent<Incrementer>("Incrementer");
  registerComponent<PerlinNoiseComponent>("Perlin noise");
  registerComponent<PixelXComponent>("Pixel.x");
  registerComponent<TimeComponent>("Time");
  registerComponent<TranslateComponent>("Translate");
}

vector<string> ComponentRegistrar::getAvailableComponents()
{
  vector<string> keys;
  keys.reserve(componentFactories.size());
  for(auto kv : componentFactories) {
      keys.push_back(kv.first);
  }
  return keys;
}
