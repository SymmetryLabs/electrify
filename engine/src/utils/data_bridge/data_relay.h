#pragma once

#include <memory>
#include <vector>

#include "incoming_data_relay.h"
#include "outgoing_data_relay.h"

class EventQueue;
class DataProxy;

class DataRelay {

public:
    DataRelay();
    DataRelay(const std::shared_ptr<EventQueue>& outgoingQueue,
        const std::shared_ptr<EventQueue>& incomingQueue);

    void commitOutgoingTransaction();
    unsigned int processIncomingTransactions();
    void processIncomingTransactionsUpTo(unsigned int id);

    void flush();

    DataProxy& getProxy();
    OutgoingDataRelay& getOutgoingDataRelay();
    IncomingDataRelay& getIncomingDataRelay();
    unsigned int getLastFrameId() const;

    void addAuxOutgoingDataRelay(OutgoingDataRelay& outgoingDataRelay);
    void removeAuxOutgoingDataRelay(OutgoingDataRelay& outgoingDataRelay);

private:
    OutgoingDataRelay outgoingDataRelay;
    IncomingDataRelay incomingDataRelay;

    unsigned int frameId = 0;

    std::vector<OutgoingDataRelay*> auxOutgoingDataRelays;

};
