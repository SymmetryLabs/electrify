#include "engine_ui.h"

EngineUi::EngineUi(Engine& engine_)
  : engine(engine_)
{
  addObserver(Observe(engine.preFrameUpdateEvent, [this] (Token) {
    proxyBridge.processUpstreamFlowingTransactions();
  }));
  addObserver(Observe(engine.postFrameUpdateEvent, [this] (Token) {
    proxyBridge.commitDownstreamFlowingTransaction();
  }));

  auto engineBlueprint = dynamic_pointer_cast<CompoundNode>(engine.getRenderable());
  blueprint = makeProxy<EngineUiDomain>(engineBlueprint, proxyBridge);
  nodeGrid = make_unique<NodeGrid>(blueprint.get());
}

void EngineUi::commitUpstreamFlowingTransaction()
{
  proxyBridge.commitUpstreamFlowingTransaction();
}

void EngineUi::processDownstreamFlowingTransactions()
{
  proxyBridge.processDownstreamFlowingTransactions();
}
