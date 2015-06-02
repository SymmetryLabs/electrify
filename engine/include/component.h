#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstddef>
#include "pixel.h"
#include "group.h"
#include "color.h"

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide outputs.
 * A component can contain other components.
 */
class Component {
public:
	Component();
	~Component();
	
	Color* calculate(Pixel *pixel, Group *topLevel /*, frameContext */);
	void update(double time);

};


#endif // COMPONENT_H