#include "app.h"
#include <iostream>
#include <string>
#include "color.h"
#include "constant_color_component.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"



 int main()
 {

  FrameContext *f = new FrameContext();

  ConstantColorComponent *c= new ConstantColorComponent();
  std::string color("color"); //same name for I and O
  std::cout << c->getOutput<Color>(color)->calculate_function(f)->asRGBA();
  std::cout << '\n';
  ColorDoubler *colorDoubler = new ColorDoubler();
  colorDoubler->wireInput<Color>(color, c->getOutput<Color>(color));
  std::cout << colorDoubler->getOutput<Color>(color)->calculate_function(f)->asRGBA();
  std::cout << '\n';
  
  SquareWave *sq = new SquareWave();
  std::string value("value");
  
  Signal<double> *ds = sq->getOutput<double>(value);

  double *d = ds->calculate_function(f);
  std::cout << *d;
  std::cout << '\n';

  f->time = 0.8;

  std::cout << *(sq->getOutput<double>(value)->calculate_function(f));
  std::cout << '\n';

  Incrementer *incr = new Incrementer();
  incr->wireInput<Color>(color, colorDoubler->getOutput<Color>(color));
  std::cout << incr->getOutput<Color>(color)->calculate_function(f)->asRGBA();
  std::cout << '\n';

  incr->update(f);
  std::cout << incr->getOutput<Color>(color)->calculate_function(f)->asRGBA();
  std::cout << '\n';

  incr->update(f);
  std::cout << incr->getOutput<Color>(color)->calculate_function(f)->asRGBA();
  std::cout << '\n';

  return 0;
 }