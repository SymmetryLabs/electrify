#include "app.h"

#include "color.h"
#include "constant_color_component.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"
#include "engine.h"
#include "loader.h"
#include "compound_component.h"
#include "translate_component.h"
#include "blueprint.h"
#include "component_registrar.h"

int main()
{
  FrameContext frame {nanoseconds(100)};

  ConstantColorComponent c;
  cout << c.getOutput<Color>("output")->calculate(frame) << endl;

  ColorDoubler colorDoubler;
  colorDoubler.wireInput("color", *c.getOutput<Color>("output"));
  cout << colorDoubler.getOutput<Color>("output")->calculate(frame) << endl;
  
  SquareWave sq;
  
  SignalX<double> *ds = sq.getOutput<double>("output");

  double d = ds->calculate(frame);
  cout << d << endl;

  cout << sq.getOutput<double>("output")->calculate(frame) << endl;

  Incrementer incr;
  incr.wireInput("color", *colorDoubler.getOutput<Color>("output"));
  cout << incr.getOutput<Color>("output")->calculate(frame) << endl;

  incr.update(frame);
  cout << incr.getOutput<Color>("output")->calculate(frame) << endl;

  incr.update(frame);
  cout << incr.getOutput<Color>("output")->calculate(frame) << endl;


  ComponentRegistrar componentRegistrar;
  cout << componentRegistrar.getAvailableComponents()[0] << endl;


  auto blueprint = make_shared<Blueprint>();
  auto model = make_unique<Model>();
  model->pixels = {new Pixel()};

  auto compound = blueprint->makeSubcomponent<CompoundComponent>();
  compound->registerWirableOutput<Color>("color");

  auto constantColor = compound->makeSubcomponent<ConstantColorComponent>();
  auto translateComponent = compound->makeSubcomponent<TranslateComponent>();

  compound->wireSubcomponents(*constantColor, "output", *translateComponent, "signalInput");
  compound->wireOutput("color", *translateComponent, "output");

  blueprint->wireOutput("color", *compound, "color");
  
  Engine engine(blueprint, move(model));
  engine.startAndWait();
 
  return 0;
 }