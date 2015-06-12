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
  cout << c.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  ColorDoubler colorDoubler;
  colorDoubler.wireInput("color", c.getOutput<Color>("color"));
  cout << colorDoubler.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;
  
  SquareWave sq;
  
  Signal<double> *ds = sq.getOutput<double>("value");

  double d = ds->calculate(frag);
  cout << d << endl;

  frag.time = 0.8;

  cout << sq.getOutput<double>("value")->calculate(frag) << endl;

  Incrementer incr;
  incr.wireInput("color", colorDoubler.getOutput<Color>("color"));
  cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  incr.update(f);
  cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  incr.update(f);
  cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

  auto blueprint = unique_ptr<Blueprint> {new Blueprint()};
  auto model = unique_ptr<Model> {new Model()};
  model->pixels = {Pixel()};
  cout << model->pixels.size() << endl;

  auto compound = unique_ptr<CompoundComponent> {new CompoundComponent()};
  auto comp = unique_ptr<ConstantColorComponent> {new ConstantColorComponent()};
  compound->addSubcomponent(move(comp));
  blueprint->outputSocket.signal = compound->getOutput<Color>("color");
  blueprint->addSubcomponent(move(compound));
  
  Engine engine(move(blueprint), move(model));
  engine.startAndWait();
 
  return 0;
 }