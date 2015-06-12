#pragma once
#include "constants.h"

#include "component.h"

class CompoundComponent : public Component {

public:
  CompoundComponent();
  virtual ~CompoundComponent() {}

  virtual void init() override;
  virtual void update(const FrameContext& f) override;
  Color calculate_color(const FragmentContext& frag);

  void addSubcomponent(unique_ptr<Component> subcomponent);
  void removeSubcomponent(const unique_ptr<Component>& subcomponent);

private:
  vector<unique_ptr<Component>> subcomponents;

};
