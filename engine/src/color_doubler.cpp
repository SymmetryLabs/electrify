#include "color_doubler.h"
#include <string>
#include "color.h"
#include "signals.h"
#include "frame_context.h"

ColorDoubler::ColorDoubler()
{
  std::string colorOutputName("color");
  ColorSignal* colorSignal =  new ColorSignal();
  colorSignal->calculate_function = [this] 
    (FrameContext *f) 
    {
      return this->double_color(f);
    };
  std::string colorInputName("color");
  addOutput(colorOutputName,(BaseSignal*) colorSignal);
  InputSocket<Color> *colorSocket = new InputSocket<Color>();
  addInputSocket(colorInputName, colorSocket);
};

Color* ColorDoubler::double_color(FrameContext *f)
{
  std::string colorInputName("color");
  Color *in=((ColorSignal*) ((InputSocket<Color>*) inputs[colorInputName])->input_signal)->calculate_function(f);
  in->fromRGBA(in->asRGBA()*2);
  return in;
};