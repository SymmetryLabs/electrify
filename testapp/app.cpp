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
  cout << "start" << endl;

  FrameContext frame {nanoseconds(100)};

  ConstantColorNode c;
  cout << c.calculate(frame) << endl;

  ColorDoubler colorDoubler;
  c.getOutput("output")->wireOutput(*colorDoubler.getInput("color"));
  cout << colorDoubler.calculate(frame) << endl;
  
  SquareWave sq;

  cout << sq.calculate(frame) << endl;

  Incrementer incr;
  colorDoubler.getOutput("output")->wireOutput(*incr.getInput("color"));
  cout << incr.calculate(frame) << endl;

  incr.update(frame);
  cout << incr.calculate(frame) << endl;

  incr.update(frame);
  cout << incr.calculate(frame) << endl;


  NodeRegistrar nodeRegistrar;
  cout << nodeRegistrar.getAvailableNodeNames()[0] << endl;


  auto blueprint = make_shared<Blueprint>();
  auto model = make_unique<Model>();
  model->pixels = {new Pixel()};

  auto compound = blueprint->makeSubnode<CompoundNode>();
  compound->registerWirableOutput<Color>("color");

  auto constantColor = compound->makeSubnode<ConstantColorNode>();
  auto translateNode = compound->makeSubnode<TranslateNode>();

  compound->wireSubnodes(*constantColor->getOutput("output"), *translateNode->getInput("Translate"));
  compound->wireSubnodes(*translateNode->getOutput("Translate"), *compound->getWirableOutput("color"));

  compound->wireSubnodes(*compound->getOutput("color"), *blueprint->getWirableOutput("color"));
  
  Engine engine(blueprint, move(model));
  engine.startAndWait();
 
  return 0;
 }