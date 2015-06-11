#pragma once
#include "constants.h"

#include <cstddef>
#include <unordered_map>
#include "observer.h"
#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signal.h"
#include <functional>
#include "frame_context.h"

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component : public Observable, public Observer 
{
  public:
  unordered_map<string, BaseSignal*> inputs;
  unordered_map<string, BaseSignal*> outputs;

  void notify(/*TODO PASSING FORMAT*/);
  
  /**
   * Tells the component to update its model according to the current time
  */
  void update(FrameContext f);
  // The casting to BaseSignal is so we can store differing concrete type signals in the same vector
  template <class T> void addOutput(string output_name, Signal<T> *output_signal)
  {
    outputs[output_name] = (BaseSignal*) output_signal;
  };

  template <class T> Signal<T>* getOutput(string output_name)
  {
    return (Signal<T>*) outputs[output_name];
  };

  template <class T> void addInputSocket(string input_name, InputSocket<T> *input_socket)
  {
    inputs[input_name] = (BaseSignal*) input_socket;
  };

  template <class T> InputSocket<T>* getInputSocket(string input_name)
  {
    return (InputSocket<T>*) inputs[input_name];
  };

  template <class T> void wireInput(string input_name, Signal<T> *input_signal)
  {
    ((InputSocket<T>*) inputs[input_name])->input_signal = input_signal;
  };
};
    


