#include "app.h"
#include <iostream>

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

int main()
{
 /* file loading */
//  cout << "trying to load file\n";
//  Loader loader = Loader();
//  string filename("data/dummydata.json");
//  loader.loadJSON(filename);
//  cout << "file loaded\n";

  FrameContext frame {nanoseconds(100)};

  ConstantColorComponent c;
  cout << c.getOutput<Color>("primary")->calculate(frame) << endl;

  ColorDoubler colorDoubler;
  colorDoubler.wireInput("color", *c.getOutput<Color>("primary"));
  cout << colorDoubler.getOutput<Color>("primary")->calculate(frame) << endl;
  
  SquareWave sq;
  
  Signal<double> *ds = sq.getOutput<double>("primary");

  double d = ds->calculate(frame);
  cout << d << endl;

  cout << sq.getOutput<double>("primary")->calculate(frame) << endl;

  Incrementer incr;
  incr.wireInput("color", *colorDoubler.getOutput<Color>("primary"));
  cout << incr.getOutput<Color>("primary")->calculate(frame) << endl;

  incr.update(frame);
  cout << incr.getOutput<Color>("primary")->calculate(frame) << endl;

  incr.update(frame);
  cout << incr.getOutput<Color>("primary")->calculate(frame) << endl;



  auto blueprint = make_unique<Blueprint>();
  auto model = make_unique<Model>();
  model->pixels = {new Pixel()};

  auto compound = blueprint->makeSubcomponent<CompoundComponent>();
  compound->registerWirableOutput<Color>("color");

  auto constantColor = compound->makeSubcomponent<ConstantColorComponent>();
  auto translateComponent = compound->makeSubcomponent<TranslateComponent>();

  compound->wireSubcomponents(*constantColor, "primary", *translateComponent, "signalInput");
  compound->wireOutput("color", *translateComponent, "primary");

  blueprint->wireOutput("color", *compound, "color");

  cout << "Is blueprint fully wired: " << blueprint->isFullyWired() << endl;
  
  Engine engine(move(blueprint), move(model));
  engine.startAndWait();
 
  return 0;
 }