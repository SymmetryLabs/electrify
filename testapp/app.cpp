#include "app.h"
#include <iostream>
#include <string>
#include "constant_color_component.h"
#include "signals.h"
#include "pixel.h"
#include "group.h"


 int main()
 {
 	ConstantColorComponent *c= new ConstantColorComponent();
 	std::string color("color");
 	std::cout << ((ColorSignal*) c->outputs[color])->calculate_function(new Pixel(),new Group())->test;
 	return 0;
 }