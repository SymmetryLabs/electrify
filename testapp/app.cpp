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



 int main()
 {
 	ConstantColorComponent *c= new ConstantColorComponent();
 	std::string color("color"); //same name for I and O
 	std::cout << c->getOutput<Color>(color)->calculate_function(new FrameContext())->asRGBA();
 	ColorDoubler *colorDoubler = new ColorDoubler();
 	colorDoubler->wireInput<Color>(color, c->getOutput<Color>(color));
 	std::cout << colorDoubler->getOutput<Color>(color)->calculate_function(new FrameContext())->asRGBA();
 	return 0;
 }