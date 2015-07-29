#pragma once
#include "globals.h"

#include "component.h"
#include "socket.h"
#include "observable_vector.h"
#include "data_proxy.h"

class CompoundComponent : public Component {

public:
  static const string componentName() { return "Compound Component"; }

  virtual void init() override;
  virtual void deinit() override;
  virtual void update(const FrameContext& f) override;

  template <typename Type, typename... Targs>
  Type* makeSubcomponent(Targs&&... Fargs);
  Component* createSubcomponent(const string& name);

  void addSubcomponent(unique_ptr<Component> subcomponent);
  void removeSubcomponent(Component* subcomponent);

  bool canWireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
    Component& receivingSubcomponent, const string& receivingInputName);
  void wireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
    Component& receivingSubcomponent, const string& receivingInputName);
  void unwireSubcomponents(Component& emittingSubcomponent, const string& emittingOutputName,
    Component& receivingSubcomponent, const string& receivingInputName);

  template <typename V>
  Socket<V>* registerWirableOutput(const string& name);

  BaseSocket* getWirableOutput(const string& name);
  void wireOutput(const string& name,
    Component& emittingSubcomponent, const string& emittingOutputName);

  ObservableVector<EngineDomain, shared_ptr<Component>> subcomponents;

private:
  unordered_map<string, BaseSocket*> wirableOutputs;

};

template<typename Domain>
class CompoundComponentProxy : public ComponentProxy<Domain> {

public:
  explicit CompoundComponentProxy(shared_ptr<CompoundComponent> master, ProxyBridge& proxyBridge)
    : ComponentProxy<Domain>(master, proxyBridge)
  {
    master->subcomponents.makeProxySlave<Domain, ComponentProxy<Domain>>(subcomponents, proxyBridge);
  }

  ObservableVector<Domain, shared_ptr<ComponentProxy<Domain>>, EngineDomain> subcomponents;

  void addSubcomponent(const string& name)
  {
    this->template sendCommand<CompoundComponent>([=] (shared_ptr<CompoundComponent> compoundComponent) {
      compoundComponent->createSubcomponent(name);
    });
  }
};

template<typename Domain>
shared_ptr<CompoundComponentProxy<Domain>> makeProxy(shared_ptr<CompoundComponent> object, ProxyBridge& proxyBridge) {
  return make_shared<CompoundComponentProxy<Domain>>(object, proxyBridge);
}

#include "compound_component.tpp"
