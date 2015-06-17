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
#include "blueprint.h"

int main()
{
 /* file loading */
//  cout << "trying to load file\n";
//  Loader loader = Loader();
//  string filename("data/dummydata.json");
//  loader.loadJSON(filename);
//  cout << "file loaded\n";

  FrameContext f {nanoseconds(100)};
  FragmentContext frag {Pixel(), f};

  ConstantColorComponent c;
  cout << c.getOutput<Color>("value")->calculate(frag) << endl;

  ColorDoubler colorDoubler;
  colorDoubler.wireInput("color", c.getOutput<Color>("value"));
  cout << colorDoubler.getOutput<Color>("value")->calculate(frag) << endl;
  
  SquareWave sq;
  
  Signal<double> *ds = sq.getOutput<double>("value");

  double d = ds->calculate(frag);
  cout << d << endl;

  cout << sq.getOutput<double>("value")->calculate(frag) << endl;

  Incrementer incr;
  incr.wireInput("color", colorDoubler.getOutput<Color>("value"));
  cout << incr.getOutput<Color>("value")->calculate(frag) << endl;

  incr.update(f);
  cout << incr.getOutput<Color>("value")->calculate(frag) << endl;

  incr.update(f);
  cout << incr.getOutput<Color>("value")->calculate(frag) << endl;

  unique_ptr<Blueprint> blueprint {new Blueprint()};
  unique_ptr<Model> model {new Model()};
  model->pixels = {Pixel()};

  unique_ptr<CompoundComponent> compound {new CompoundComponent()};
  compound->registerWirableOutput<Color>("color");

  unique_ptr<ConstantColorComponent> comp {new ConstantColorComponent()};
  compound->wireOutput("color", comp->getOutput<Color>("value"));
  compound->addSubcomponent(move(comp));

  blueprint->wireOutput("color", compound->getOutput<Color>("color"));
  blueprint->addSubcomponent(move(compound));

  cout << "Is blueprint fully wired: " << blueprint->isFullyWired() << endl;
  
  Engine engine(move(blueprint), move(model));
  engine.startAndWait();
 
  return 0;
 }