#include "data_relay.h"

#include "event_queue.h"

DataRelay::DataRelay(EventQueue& outgoingQueue_,
    EventQueue& incomingQueue_)
: outgoingQueue(outgoingQueue_)
, incomingQueue(incomingQueue_)
{
}

void DataRelay::queueEvent(const std::function<void()>& eventFunc)
{
    outgoingQueue.queueEvent(eventFunc);
}

void DataRelay::commitOutgoingTransaction()
{
    outgoingQueue.commitTransaction();
}

void DataRelay::processIncomingTransactions()
{
    incomingQueue.processTransactions();
}
