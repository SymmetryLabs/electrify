#pragma once

#include <functional>

class EventQueue;

class DataProxy {

public:
    DataProxy() = default;
    explicit DataProxy(std::shared_ptr<EventQueue> eventQueue);

    template <typename F>
    void sendEvent(F&& eventFunc);

private:
    std::weak_ptr<EventQueue> eventQueue;
    bool hasEventQueue() const;
    EventQueue& getEventQueue() const;

    void queueEvent(const std::function<void()>& eventFunc);

};

#include "data_proxy.hpp"
