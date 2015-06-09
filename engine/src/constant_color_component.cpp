#include "constant_color_component.h"
#include "signal.h"
#include "frame_context.h"

ConstantColorComponent::ConstantColorComponent()
{
    string colorOutputName("color");
    Signal<Color>* colorSignal =  new Signal<Color>();
    colorSignal->calculate_function = [this]
      (FrameContext f)
      {
        return this->calculate_color(f);
      };
    addOutput<Color>(colorOutputName, colorSignal);
}