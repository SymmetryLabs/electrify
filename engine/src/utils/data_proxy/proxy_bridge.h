#pragma once

#include <functional>

#include <boost/uuid/uuid.hpp>

#include "event_queue.h"

class ProxyBridge {

public:
    ProxyBridge();

    boost::uuids::uuid uuid;

    void queueDownstreamEvent(const std::function<void()>& eventFunc);
    void commitDownstreamFlowingTransaction();
    void processDownstreamFlowingTransactions();

    void queueUpstreamEvent(const std::function<void()>& eventFunc);
    void commitUpstreamFlowingTransaction();
    void processUpstreamFlowingTransactions();

private:

    EventQueue downstreamFlowingEventQueue;
    EventQueue upstreamFlowingEventQueue;

};
