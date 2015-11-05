#include "event_queue.h"

#include "numerical_utils.h"

EventQueue::EventQueue()
: transactionQueue{0}
, nextTransaction(nullptr)
{
}

EventQueue::~EventQueue()
{
    if (nextTransaction) {
        delete nextTransaction;
    }
    transactionQueue.consume_all([] (Transaction* transaction) {
        delete transaction;
    });
}

void EventQueue::queueEvent(const std::function<void()>& eventFunc)
{
    eventBuffer.push_back(eventFunc);
}

bool EventQueue::commitTransaction(unsigned int id, bool forceTransaction)
{
    if (!eventBuffer.empty() || forceTransaction) {
        transactionQueue.push(new Transaction(id, eventBuffer));
        return true;
    }
    return false;
}

unsigned int EventQueue::processTransactions()
{
    if (nextTransaction) {
        for (std::function<void()> eventFunc : nextTransaction->events) {
            eventFunc();
        }
        lastTransactionId = nextTransaction->id;
        delete nextTransaction;
        nextTransaction = nullptr;
    }
    transactionQueue.consume_all([this] (Transaction* transaction) {
        for (std::function<void()> eventFunc : transaction->events) {
            eventFunc();
        }
        lastTransactionId = transaction->id;
        delete transaction;
    });
    return lastTransactionId;
}

void EventQueue::processTransactionsUpTo(unsigned int id)
{
    while ((nextTransaction || transactionQueue.pop(nextTransaction))
            && (compareWithOverflow(nextTransaction->id, id) <= 0)) {
        for (std::function<void()> eventFunc : nextTransaction->events) {
            eventFunc();
        }
        lastTransactionId = nextTransaction->id;
        delete nextTransaction;
        nextTransaction = nullptr;
    }
}

void EventQueue::flush()
{
    commitTransaction();
    processTransactions();
}

EventQueue::Transaction::Transaction(unsigned int id_, std::vector<std::function<void()>>& eventBuffer)
: id(id_)
{
    events.swap(eventBuffer);
}
