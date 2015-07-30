#pragma once
#include "globals.h"

#include <cstddef>
#include <functional>
#include <unordered_map>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signals.h"
#include "socket.h"
#include "frame_context.h"
#include "parameter.h"
#include "engine.h"
#include "data_proxy.h"

static boost::uuids::random_generator componentUuidGenerator;

/**
 * Components are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A component can contain other components.
 */
class Component {

protected:
  USING_REACTIVE_DOMAIN(EngineDomain)

public:
  virtual ~Component() {}

  template<typename ConcreteType, typename... Targs>
  static ConcreteType* createComponent(Targs&&... Fargs) {
    ConcreteType* component = new ConcreteType(forward<Targs>(Fargs)...);
    component->name <<= ConcreteType::componentName();
    component->uuid = componentUuidGenerator();
    return component;
  }

  VarSignalT<string> name = MakeVar<EngineDomain>(string());
  boost::uuids::uuid uuid;

  virtual void init() {}
  virtual void deinit() {}

  /**
   * Tells the component to update its model according to the current time
   */
  virtual void update(__attribute__((unused)) const FrameContext& f) {}

  // Input

  void registerInput(const string& name, unique_ptr<BaseSocket> inputSocket);
  template <typename V>
  void registerInput(const string& name, SignalX<V>** inputAddr);
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
  SignalX<V>* getOutput(const string& name) const;

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

template<typename Domain>
class ComponentProxy : public DataProxy<EngineDomain, Domain> {

public:
  explicit ComponentProxy(shared_ptr<Component> master, ProxyBridge& proxyBridge)
    : DataProxy<EngineDomain, Domain>(master, proxyBridge)
  {
    this->bindSignal(master->name, this->name);
    this->name <<= master->name.Value();
  }

  VarSignal<Domain, string> name = MakeVar<Domain>(string());

  void setName(const string& name_)
  {
    this->template sendCommand([=] (shared_ptr<Component> component) {
      component->name <<= name_;
    });
  }
};

template<typename Domain>
shared_ptr<ComponentProxy<Domain>> makeProxy(shared_ptr<Component> object, ProxyBridge& proxyBridge) {
  return make_shared<ComponentProxy<Domain>>(object, proxyBridge);
}

#include "component.tpp"
