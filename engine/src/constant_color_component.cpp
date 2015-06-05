#include "constant_color_component.h"
#include <string>
#include "signals.h"
#include "frame_context.h"

ConstantColorComponent::ConstantColorComponent()
{
    std::string colorOutputName("color");
    ColorSignal* colorSignal =  new ColorSignal();
    colorSignal->calculate_function = [this] 
      (FrameContext *f) 
      {
        return this->calculate_color(f);
      };
    addOutput(colorOutputName,(BaseSignal*) colorSignal);
}