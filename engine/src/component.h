#pragma once
#include "constants.h"

#include <cstddef>
#include <functional>
#include <unordered_map>

#include "observer.h"
#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signal.h"
#include "fragment_context.h"
#include "updatable.h"

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component : public Updatable, public Observable, public Observer  {

public:
  Component() {}
  virtual ~Component() {}

  virtual void notify(/*TODO PASSING FORMAT*/) {}

  void registerOutput(const string& name, unique_ptr<BaseSignal> signal);

  template <class V, class C>
  void registerOutput(const string& name, 
    V (C::* calculate_function_)(const FragmentContext& frag));

  template <class V>
  Signal<V>* getOutput(const string& name);

  void registerInput(const string& name, unique_ptr<BaseSocket> input);

  template <class V>
  Socket<V>* getInput(const string& name);

  template <class V>
  void wireInput(const string& name, Signal<V>* signal);

private:
  unordered_map<string, unique_ptr<BaseSocket>> inputs;
  unordered_map<string, unique_ptr<BaseSignal>> outputs;

};

#include "component.tpp"
