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

  FrameContext f;
  FragmentContext frag {Pixel()};

  ConstantColorComponent c;
  cout << hex << c.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  ColorDoubler colorDoubler;
  colorDoubler.wireInput("color", c.getOutput<Color>("color"));
  cout << hex << colorDoubler.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;
  
  SquareWave sq;
  
  Signal<double> *ds = sq.getOutput<double>("value");

  double d = ds->calculate(frag);
  cout << d << endl;

  frag.time = 0.8;

  cout << sq.getOutput<double>("value")->calculate(frag) << endl;

  Incrementer incr;
  incr.wireInput("color", colorDoubler.getOutput<Color>("color"));
  cout << hex << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  incr.update(f);
  cout << hex << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  incr.update(f);
  cout << hex << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  unique_ptr<Blueprint> blueprint {new Blueprint()};
  unique_ptr<Model> model {new Model()};
  model->pixels = {Pixel()};

  unique_ptr<CompoundComponent> compound {new CompoundComponent()};
  compound->registerWirableOutput<Color>("color");

  unique_ptr<ConstantColorComponent> comp {new ConstantColorComponent()};
  compound->wireOutput("color", comp->getOutput<Color>("color"));
  compound->addSubcomponent(move(comp));

  blueprint->wireOutput("color", compound->getOutput<Color>("color"));
  blueprint->addSubcomponent(move(compound));

  cout << "Is blueprint fully wired: " << blueprint->isFullyWired() << endl;
  
  Engine engine(move(blueprint), move(model));
  engine.startAndWait();
 
  return 0;
 }