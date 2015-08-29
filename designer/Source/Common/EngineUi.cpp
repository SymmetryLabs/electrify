#include "EngineUi.h"

EngineUi::EngineUi(Engine& engine_)
    : engine(engine_)
{
    observe(engine.preFrameUpdateEvent, [this] (void*) {
        proxyBridge.processUpstreamFlowingTransactions();
    });
    observe(engine.postFrameUpdateEvent, [this] (void*) {
        proxyBridge.commitDownstreamFlowingTransaction();
    });

    auto engineBlueprint = dynamic_pointer_cast<CompoundNode>(engine.getRenderable());
    blueprint = engineBlueprint->getProxy<CompoundNodeProxy>(proxyBridge);
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
