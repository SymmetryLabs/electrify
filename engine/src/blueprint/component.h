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
  virtual ~Component() {}

  template<typename ConcreteType>
  static ConcreteType* createComponent() {
    ConcreteType* component = new ConcreteType();
    component->name = ConcreteType::componentName();
    return component;
  }

  string name;

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

  BaseSocket* getInput(const string& name) const;

  virtual bool canWireInput(const string& name, const BaseSignal& signal) const;
  virtual void wireInput(const string& name, BaseSignal& signal);

  virtual void registerContextModifier(const string& name,
    ContextModifierChain& contextModifier);

  // Output

  void registerOutput(const string& name, unique_ptr<BaseSignal> signal);
  template <typename V, typename C>
  void registerOutput(const string& name, 
    V (C::* calculate_function_)(const FrameContext& frame) const);

  BaseSignal* getOutput(const string& name) const;

  template <typename V>
  Signal<V>* getOutput(const string& name) const;

  virtual bool canWireOutputTo(const string& emittingOutputName,
    const Component& receivingComponent, const string& receivingInputName) const;
  virtual bool canWireOutputTo(const string& emittingOutputName,
    const BaseSocket& receivingSocket) const;

  virtual void wireOutputTo(const string& emittingOutputName,
    Component& receivingComponent, const string& receivingInputName);
  virtual void wireOutputTo(const string& emittingOutputName,
    BaseSocket& receivingSocket);

  // Parameter

  void registerParameter(const string& name, unique_ptr<BaseParameter> parameter);

private:
  unordered_map<string, unique_ptr<BaseSocket>> inputs;
  unordered_map<string, unique_ptr<BaseSignal>> outputs;
  unordered_map<string, unique_ptr<BaseParameter>> parameters;

};

#include "component.tpp"
