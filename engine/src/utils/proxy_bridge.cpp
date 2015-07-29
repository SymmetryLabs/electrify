#include "proxy_bridge.h"

void ProxyBridge::queueDownstreamEvent(const function<void()>& eventFunc)
{
  downstreamFlowingEventQueue.queueEvent(eventFunc);
}

void ProxyBridge::commitDownstreamFlowingTransaction()
{
  downstreamFlowingEventQueue.commitTransaction();
}

void ProxyBridge::processDownstreamFlowingTransactions()
{
  downstreamFlowingEventQueue.processTransactions();
}

void ProxyBridge::queueUpstreamEvent(const function<void()>& eventFunc)
{
  upstreamFlowingEventQueue.queueEvent(eventFunc);
}

void ProxyBridge::commitUpstreamFlowingTransaction()
{
  upstreamFlowingEventQueue.commitTransaction();
}

void ProxyBridge::processUpstreamFlowingTransactions()
{
  upstreamFlowingEventQueue.processTransactions();
}
