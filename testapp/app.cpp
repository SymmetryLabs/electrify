#include "app.h"
#include <iostream>
#include <string>
#include "constant_color_component.h"
#include "color_doubler.h"
#include "signals.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"


 int main()
 {
 	ConstantColorComponent *c= new ConstantColorComponent();
 	std::string color("color"); //same name for I and O
 	std::cout << ((ColorSignal*) c->outputs[color])->calculate_function(new FrameContext())->asRGBA();
 	ColorDoubler *colorDoubler = new ColorDoubler();
 	colorDoubler->wireInput<Color>(color,(Signal<Color>*) c->outputs[color]);
 	std::cout << ((ColorSignal*) colorDoubler->outputs[color])->calculate_function(new FrameContext())->asRGBA();
 	return 0;
 }