#pragma once

class EventQueue;

class DataRelay {

public:
    DataRelay(EventQueue& outgoingQueue, EventQueue& incomingQueue);

    void commitOutgoingTransaction();
    void processIncomingTransactions();

private:
    EventQueue& outgoingQueue;
    EventQueue& incomingQueue;

};
