#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstddef>
#include "observer.h"
#include "pixel.h"
#include "group.h"
#include "color.h"

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component : public  Observable, public Observer 
{
  public:
  // TODO need a list of inputs
    // TODO need a list of outputs
    // TODO need methods for adding and retrieving inputs and outputs
  
  Component();
  ~Component();

  void notify(/*TODO PASSING FORMAT*/);
  
  /**
     * Tells the component to update its model according to the current time
    */
  void update(double time);
  /**
     * Called by another component to finally render a color based on component state
    */
  Color* calculate(Pixel *pixel, Group *topLevel /*, frameContext */);
};


#endif // COMPONENT_H