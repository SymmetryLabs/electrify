#pragma once

#include <memory>

class EventQueue;

class IncomingDataRelay {

public:
    IncomingDataRelay() = default;
    explicit IncomingDataRelay(const std::shared_ptr<EventQueue>& queue);

    unsigned int processTransactions();
    void processTransactionsUpTo(unsigned int id);

private:
    std::shared_ptr<EventQueue> queue;

};
