#include "constant_color_component.h"
#include <string>
#include "signals.h"

ConstantColorComponent::ConstantColorComponent()
{
    std::string colorOutputName("color");
    ColorSignal* colorSignal =  new ColorSignal();
    colorSignal->calculate_function = [this] 
      (Pixel *pixel, Group *topLevel /*, frameContext */) 
      {
        return this->calculate_color(pixel,topLevel /*, frameContext */);
      };
    addOutput(colorOutputName,(BaseSignal*) colorSignal);
}