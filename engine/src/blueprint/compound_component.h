#pragma once
#include "globals.h"

#include "component.h"
#include "socket.h"

class CompoundComponent : public Component {

public:
  virtual ~CompoundComponent() {}

  static const string componentName() { return "Compound Component"; }

  virtual void init() override;
  virtual void deinit() override;
  virtual void update(const FrameContext& f) override;

  template <typename Type, typename... Targs>
  Type* makeSubcomponent(Targs&&... Fargs);
  void addSubcomponent(unique_ptr<Component> subcomponent);
  void removeSubcomponent(const unique_ptr<Component>& subcomponent);

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

private:
  vector<unique_ptr<Component>> subcomponents;
  unordered_map<string, BaseSocket*> wirableOutputs;

};

#include "compound_component.tpp"
