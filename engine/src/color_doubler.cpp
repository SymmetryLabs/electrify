#include "color_doubler.h"
#include <string>
#include "color.h"
#include "signals.h"

ColorDoubler::ColorDoubler()
{
  std::string colorOutputName("color");
  ColorSignal* colorSignal =  new ColorSignal();
  colorSignal->calculate_function = [this] 
    (Pixel *pixel, Group *topLevel /*, frameContext */) 
    {
      return this->double_color(pixel,topLevel /*, frameContext */);
    };
  std::string colorInputName("color");
  addOutput(colorOutputName,(BaseSignal*) colorSignal);
  InputSocket<Color> *colorSocket = new InputSocket<Color>();
  addInputSocket(colorInputName, colorSocket);
};

Color* ColorDoubler::double_color(Pixel *pixel, Group *topLevel /*, frameContext */)
{
  std::string colorInputName("color");
  Color *in=((ColorSignal*) ((InputSocket<Color>*) inputs[colorInputName])->input_signal)->calculate_function(pixel,topLevel);
  in->fromRGBA(in->asRGBA()*2);
  return in;
};