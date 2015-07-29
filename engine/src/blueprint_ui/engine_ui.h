#pragma once
#include "blueprint_ui_globals.h"

#include "engine.h"
#include "component_grid.h"
#include "blueprint.h"
#include "proxy_bridge.h"
#include "observes.h"

class EngineUi : public Observes<EngineDomain> {

  USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
  explicit EngineUi(Engine& engine);

  shared_ptr<CompoundComponentProxy<EngineUiDomain>> blueprint;

  unique_ptr<ComponentGrid> componentGrid;

  void commitUpstreamFlowingTransaction();
  void processDownstreamFlowingTransactions();

  ProxyBridge proxyBridge;

private:
  Engine& engine;

};
