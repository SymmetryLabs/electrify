#pragma once

#include <functional>

class EventQueue;

class DataRelay {

public:
    DataRelay(EventQueue& outgoingQueue, EventQueue& incomingQueue);

    void queueEvent(const std::function<void()>& eventFunc);
    void commitOutgoingTransaction();
    void processIncomingTransactions();

private:
    EventQueue& outgoingQueue;
    EventQueue& incomingQueue;

};
