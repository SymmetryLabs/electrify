#pragma once
#include "globals.h"

#include "component.h"
#include "socket.h"

class CompoundComponent : public Component {

public:
  CompoundComponent();
  virtual ~CompoundComponent() {}

  virtual void init() override;
  virtual void update(const FrameContext& f) override;

  virtual bool isFullyWired() override;

  template <typename Type, typename... Targs>
  Type* makeSubcomponent(Targs&&... Fargs);
  void addSubcomponent(unique_ptr<Component> subcomponent);
  void removeSubcomponent(const unique_ptr<Component>& subcomponent);

  void wireSubcomponents(Component& emittingSubcomponent, string& emittingOutputName,
    Component& receivingSubcomponent, string& receivingInputName);

  template <typename V>
  Socket<V>* registerWirableOutput(const string& name);
  template <typename V>
  Socket<V>* getWirableOutput(const string& name);

  template <typename V>
  void wireOutput(const string& name, Signal<V>* signal);

private:
  vector<unique_ptr<Component>> subcomponents;
  unordered_map<string, BaseSocket*> wirableOutputs;

};

#include "compound_component.tpp"
