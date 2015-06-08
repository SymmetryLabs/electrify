#include "incrementer.h"
#include "color_doubler.h"
#include <string>
#include "color.h"
#include "frame_context.h"
#include "signal.h"

Incrementer::Incrementer()
{
  std::string colorOutputName("color");
  Signal<Color>* colorSignal =  new Signal<Color>();
  colorSignal->calculate_function = [this]
    (FrameContext f)
    {
      return this->increment_color(f);
    };
  std::string colorInputName("color");
  addOutput<Color>(colorOutputName, colorSignal);
  InputSocket<Color> *colorSocket = new InputSocket<Color>();
  addInputSocket<Color>(colorInputName, colorSocket);
};

Color Incrementer::increment_color(FrameContext f)
{
  std::string colorInputName("color");
  Color in = getInputSocket<Color>(colorInputName)->input_signal->calculate_function(f);
  in.fromRGBA(in.asRGBA() + _increment);
  return in;
};

void Incrementer::update(FrameContext f)
{
	_increment++;
};