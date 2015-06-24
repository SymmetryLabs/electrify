#pragma once
#include "globals.h"

#include <cstddef>
#include <functional>
#include <unordered_map>

#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signals.h"
#include "socket.h"
#include "frame_context.h"
#include "parameter.h"

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component  {

public:
  Component() {}
  virtual ~Component() {}

  virtual void init() {}
  virtual void deinit() {}

  /**
   * Tells the component to update its model according to the current time
   */
  virtual void update(__attribute__((unused)) const FrameContext& f) {}

  virtual bool isFullyWired();

  // Input

  void registerInput(const string& name, unique_ptr<BaseSocket> inputSocket);

  template <typename V>
  void registerInput(const string& name, Signal<V>** inputAddr);

  template <typename V>
  void registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());

  template <typename V>
  Socket<V>* getInput(const string& name) const;

  template <typename V>
  void wireInput(const string& name, Signal<V>* signal);

  // Output

  void registerOutput(const string& name, unique_ptr<BaseSignal> signal);

  template <typename V, typename C>
  void registerOutput(const string& name, 
    V (C::* calculate_function_)(const FrameContext& frame) const);

  template <typename V>
  Signal<V>* getOutput(const string& name) const;

  // Parameter

  void registerParameter(const string& name, unique_ptr<BaseParameter> parameter);

private:
  unordered_map<string, unique_ptr<BaseSocket>> inputs;
  unordered_map<string, unique_ptr<BaseSignal>> outputs;
  unordered_map<string, unique_ptr<BaseParameter>> parameters;

};

#include "component.tpp"
