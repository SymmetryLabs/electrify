#include "color_doubler.h"

#include "color.h"
#include "frame_context.h"
#include "signal.h"

ColorDoubler::ColorDoubler()
{
  string colorOutputName("color");
  Signal<Color>* colorSignal =  new Signal<Color>();
  colorSignal->calculate_function = [this]
    (FrameContext f)
    {
      return this->double_color(f);
    };
  string colorInputName("color");
  addOutput<Color>(colorOutputName, colorSignal);
  InputSocket<Color> *colorSocket = new InputSocket<Color>();
  addInputSocket<Color>(colorInputName, colorSocket);
};

Color ColorDoubler::double_color(FrameContext f)
{
  string colorInputName("color");
  Color in = getInputSocket<Color>(colorInputName)->input_signal->calculate_function(f);
  in.fromRGBA(in.asRGBA() * 2);
  return in;
};
