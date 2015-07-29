#pragma once
#include "globals.h"

#include "event_queue.h"

class ProxyBridge {

public:

  void queueDownstreamEvent(const function<void()>& eventFunc);
  void commitDownstreamFlowingTransaction();
  void processDownstreamFlowingTransactions();

  void queueUpstreamEvent(const function<void()>& eventFunc);
  void commitUpstreamFlowingTransaction();
  void processUpstreamFlowingTransactions();

private:

  EventQueue downstreamFlowingEventQueue;
  EventQueue upstreamFlowingEventQueue;

};
