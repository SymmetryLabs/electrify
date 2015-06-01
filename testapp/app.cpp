#include <iostream>
#include "component.h"
 int main()
 {
 	Component *c= new Component();
 	std::cout << c->val;
 	return 0;
 }