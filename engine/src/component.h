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
#include "frame_context.h"

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

  void notify(/*TODO PASSING FORMAT*/);
  
  /**
     * Tells the component to update its model according to the current time
    */
  void update(FrameContext *f);
  // The casting to BaseSignal is so we can store differing concrete type signals in the same vector
  template <class T> void addOutput(std::string output_name, Signal<T> *output_signal)
  {
    outputs[output_name] = (BaseSignal*) output_signal;
  };

  template <class T> Signal<T>* getOutput(std::string output_name)
  {
    return (Signal<T>*) outputs[output_name];
  };

  template <class T> void addInputSocket(std::string input_name, InputSocket<T> *input_socket)
  {
    inputs[input_name] = (BaseSignal*) input_socket;
  };

  template <class T> InputSocket<T>* getInputSocket(std::string input_name)
  {
    return (InputSocket<T>*) inputs[input_name];
  };

  template <class T> void wireInput(std::string input_name, Signal<T> *input_signal)
  {
    ((InputSocket<T>*) inputs[input_name])->input_signal = input_signal;
  };
};
    


