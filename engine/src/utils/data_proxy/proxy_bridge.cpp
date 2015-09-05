#include "proxy_bridge.h"

#include <boost/uuid/random_generator.hpp>

ProxyBridge::ProxyBridge()
{
    static boost::uuids::random_generator nodeUuidGenerator;
    uuid = nodeUuidGenerator();
}

void ProxyBridge::queueDownstreamEvent(const std::function<void()>& eventFunc)
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

void ProxyBridge::queueUpstreamEvent(const std::function<void()>& eventFunc)
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

void ProxyBridge::flushAll()
{
    commitDownstreamFlowingTransaction();
    commitUpstreamFlowingTransaction();
    processDownstreamFlowingTransactions();
    processUpstreamFlowingTransactions();
}
