#include "data_proxy.h"

#include "event_queue.h"

DataProxy::DataProxy(std::shared_ptr<EventQueue> eventQueue_)
: eventQueue(eventQueue_)
{
}

bool DataProxy::hasEventQueue() const
{
    return !eventQueue.expired();
}

EventQueue& DataProxy::getEventQueue() const
{
    return *eventQueue.lock();
}

void DataProxy::queueEvent(const std::function<void()>& eventFunc)
{
    getEventQueue().queueEvent(eventFunc);
}
