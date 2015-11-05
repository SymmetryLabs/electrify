#include "data_relay.h"

#include "event_queue.h"
#include "container_utils.h"

DataRelay::DataRelay()
{
    auto queue = std::make_shared<EventQueue>();
    outgoingDataRelay = OutgoingDataRelay{queue};
    incomingDataRelay = IncomingDataRelay{queue};
}

DataRelay::DataRelay(const std::shared_ptr<EventQueue>& outgoingQueue,
    const std::shared_ptr<EventQueue>& incomingQueue)
: outgoingDataRelay{outgoingQueue}
, incomingDataRelay(incomingQueue)
{
}

void DataRelay::commitOutgoingTransaction()
{
    frameId++;
    bool createdTransaction = false;
    for (auto relay : auxOutgoingDataRelays) {
        createdTransaction |= relay->commitTransaction(frameId);
    }
    outgoingDataRelay.commitTransaction(frameId, createdTransaction);
}

unsigned int DataRelay::processIncomingTransactions()
{
    return incomingDataRelay.processTransactions();
}

void DataRelay::processIncomingTransactionsUpTo(unsigned int id)
{
    incomingDataRelay.processTransactionsUpTo(id);
}

void DataRelay::flush()
{
    commitOutgoingTransaction();
    processIncomingTransactions();
}

DataProxy& DataRelay::getProxy()
{
    return outgoingDataRelay.getProxy();
}

OutgoingDataRelay& DataRelay::getOutgoingDataRelay()
{
    return outgoingDataRelay;
}

IncomingDataRelay& DataRelay::getIncomingDataRelay()
{
    return incomingDataRelay;
}

unsigned int DataRelay::getLastFrameId() const
{
    return frameId;
}

void DataRelay::addAuxOutgoingDataRelay(OutgoingDataRelay& outgoingDataRelay)
{
    auxOutgoingDataRelays.push_back(&outgoingDataRelay);
}

void DataRelay::removeAuxOutgoingDataRelay(OutgoingDataRelay& outgoingDataRelay)
{
    removePtr(auxOutgoingDataRelays, &outgoingDataRelay);
}
