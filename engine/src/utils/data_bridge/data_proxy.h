#pragma once

#include <functional>

class EventQueue;

class DataProxy {

public:
    DataProxy() = default;
    explicit DataProxy(std::shared_ptr<EventQueue> eventQueue);

    template <typename F>
    void sendEvent(F&& eventFunc);

    template <typename F, typename T1>
    void sendEvent(F&& eventFunc, std::weak_ptr<T1> t1);
    template <typename F, typename T1, typename T2>
    void sendEvent(F&& eventFunc, std::weak_ptr<T1> t1, std::weak_ptr<T2> t2);

    template <typename F, typename T1>
    void sendEvent(F&& eventFunc, const T1& t1);
    template <typename F, typename T1, typename T2>
    void sendEvent(F&& eventFunc, const T1& t1, const T2& t2);

private:
    std::weak_ptr<EventQueue> eventQueue;
    bool hasEventQueue() const;
    EventQueue& getEventQueue() const;

    void queueEvent(const std::function<void()>& eventFunc);

};

#include "data_proxy.hpp"
