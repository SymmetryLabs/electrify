#pragma once
#include "BlueprintUiGlobals.h"

#include "engine.h"
#include "NodeGrid.h"
#include "blueprint.h"
#include "proxy_bridge.h"
#include "observes.h"

class EngineUi : public Observes {

public:
    explicit EngineUi(Engine& engine);

    shared_ptr<CompoundNodeProxy> blueprint;

    unique_ptr<NodeGrid> nodeGrid;

    void commitUpstreamFlowingTransaction();
    void processDownstreamFlowingTransactions();

    ProxyBridge proxyBridge;

private:
    Engine& engine;

};
