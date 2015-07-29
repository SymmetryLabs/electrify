#include "event_queue.h"

EventQueue::EventQueue()
  : transactionQueue(0)
{
}

EventQueue::~EventQueue()
{
  transactionQueue.consume_all([] (Transaction* transaction) {
    delete transaction;
  });
}

void EventQueue::queueEvent(const function<void()>& eventFunc)
{
  eventBuffer.push_back(eventFunc);
}

void EventQueue::commitTransaction()
{
  if (!eventBuffer.empty()) {
    transactionQueue.push(new Transaction(eventBuffer));
  }
}

void EventQueue::processTransactions()
{
  transactionQueue.consume_all([] (Transaction* transaction) {
    for (function<void()> eventFunc : transaction->events) {
      eventFunc();
    }
    delete transaction;
  });
}

EventQueue::Transaction::Transaction(vector<function<void()>>& eventBuffer) {
  events.swap(eventBuffer);
}
