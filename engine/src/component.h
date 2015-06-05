#pragma once
#include <cstddef>
#include <unordered_map>
#include <string>
#include "observer.h"
#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signal.h"
#include <functional>

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component : public Observable, public Observer 
{
  public:
  std::unordered_map<std::string, BaseSignal*> inputs;
  std::unordered_map<std::string, BaseSignal*> outputs;
  
  Component();
  ~Component();

  void notify(/*TODO PASSING FORMAT*/);
  
  /**
     * Tells the component to update its model according to the current time
    */
  void update(double time);
  void addOutput(std::string output_name, BaseSignal *signal);
  void addInputSocket(std::string input_name, BaseSignal *input_socket);

  template <class T> void wireInput(std::string input_name, Signal<T> *input_signal)
  {
    ((InputSocket<T>*) inputs[input_name])->input_signal = input_signal;
  };
};
    


