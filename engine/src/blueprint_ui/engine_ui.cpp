#include "engine_ui.h"

EngineUi::EngineUi(Engine& engine_)
  : engine(engine_)
{
  observers.push_back(Observe(engine.preFrameUpdateEvent, [this] (Token) {
    proxyBridge.processUpstreamFlowingTransactions();
  }));
  observers.push_back(Observe(engine.postFrameUpdateEvent, [this] (Token) {
    proxyBridge.commitDownstreamFlowingTransaction();
  }));

  auto engineBlueprint = dynamic_pointer_cast<CompoundComponent>(engine.getRenderable());
  blueprint = makeProxy<EngineUiDomain>(engineBlueprint, proxyBridge);
  componentGrid = make_unique<ComponentGrid>(blueprint.get());
}

void EngineUi::commitUpstreamFlowingTransaction()
{
  proxyBridge.commitUpstreamFlowingTransaction();
}

void EngineUi::processDownstreamFlowingTransactions()
{
  proxyBridge.processDownstreamFlowingTransactions();
}
