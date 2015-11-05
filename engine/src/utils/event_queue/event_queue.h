#pragma once

#include <functional>
#include <vector>

#include <boost/lockfree/queue.hpp>

/**
 * - Threadsafe transactional event queue.
 * - Queuing should happen on thread A, while dequeuing
 *     and executing should happen on thread B.
 * - Queuing an event puts it in a transaction buffer
 * - Thread A commits the transaction when all events for that
 *     iteration are queued, at the end of each thread A frame.
 * - Thread B processes the committed events at the beginning
 *     of each thread B frame.
 */
class EventQueue {

public:
    EventQueue();
    ~EventQueue();

    void queueEvent(const std::function<void()>& eventFunc);

    bool commitTransaction(unsigned int id = 0, bool forceTransaction = false);
    unsigned int processTransactions();
    void processTransactionsUpTo(unsigned int id);
    void flush();

private:

    struct Transaction {

        explicit Transaction(unsigned int id, std::vector<std::function<void()>>& eventBuffer);

        unsigned int id;
        std::vector<std::function<void()>> events;

    };

    std::vector<std::function<void()>> eventBuffer;
    boost::lockfree::queue<Transaction*> transactionQueue;
    Transaction* nextTransaction;
    unsigned int lastTransactionId = 0;

};
