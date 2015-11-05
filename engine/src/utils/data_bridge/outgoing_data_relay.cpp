#include "outgoing_data_relay.h"

#include "event_queue.h"

OutgoingDataRelay::OutgoingDataRelay(const std::shared_ptr<EventQueue>& queue_)
: queue(queue_)
, dataProxy{queue_}
{
}

bool OutgoingDataRelay::commitTransaction(unsigned int id, bool forceTransaction)
{
    return queue->commitTransaction(id, forceTransaction);
}

DataProxy& OutgoingDataRelay::getProxy()
{
    return dataProxy;
}
