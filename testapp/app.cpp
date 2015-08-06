#include "app.h"

#include "color.h"
#include "constant_color_node.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"
#include "engine.h"
#include "loader.h"
#include "compound_node.h"
#include "translate_node.h"
#include "blueprint.h"
#include "node_registrar.h"

int main()
{
  FrameContext frame {nanoseconds(100)};

  ConstantColorNode c;
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


  NodeRegistrar nodeRegistrar;
  cout << nodeRegistrar.getAvailableNodeNames()[0] << endl;


  auto blueprint = make_shared<Blueprint>();
  auto model = make_unique<Model>();
  model->pixels = {new Pixel()};

  auto compound = blueprint->makeSubnode<CompoundNode>();
  compound->registerWirableOutput<Color>("color");

  auto constantColor = compound->makeSubnode<ConstantColorNode>();
  auto translateNode = compound->makeSubnode<TranslateNode>();

  compound->wireSubnodes(*constantColor, "output", *translateNode, "signalInput");
  compound->wireOutput("color", *translateNode, "output");

  blueprint->wireOutput("color", *compound, "color");
  
  Engine engine(blueprint, move(model));
  engine.startAndWait();
 
  return 0;
 }