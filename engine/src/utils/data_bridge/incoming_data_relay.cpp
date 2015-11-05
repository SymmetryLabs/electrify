#include "incoming_data_relay.h"

#include "event_queue.h"

IncomingDataRelay::IncomingDataRelay(const std::shared_ptr<EventQueue>& queue_)
: queue(queue_)
{
}

unsigned int IncomingDataRelay::processTransactions()
{
    return queue->processTransactions();
}

void IncomingDataRelay::processTransactionsUpTo(unsigned int id)
{
    queue->processTransactionsUpTo(id);
}
