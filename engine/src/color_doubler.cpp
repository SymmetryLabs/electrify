#include "color_doubler.h"
#include <string>
#include "color.h"
#include "frame_context.h"
#include "signal.h"

ColorDoubler::ColorDoubler()
{
  std::string colorOutputName("color");
  Signal<Color>* colorSignal =  new Signal<Color>();
  colorSignal->calculate_function = [this]
    (FrameContext *f)
    {
      return this->double_color(f);
    };
  std::string colorInputName("color");
  addOutput(colorOutputName, colorSignal);
  InputSocket<Color> *colorSocket = new InputSocket<Color>();
  addInputSocket(colorInputName, colorSocket);
};

Color* ColorDoubler::double_color(FrameContext *f)
{
  std::string colorInputName("color");
  Color *in= getInputSocket<Color>(colorInputName)->input_signal->calculate_function(f);
  in->fromRGBA(in->asRGBA() * 2);
  return in;
};