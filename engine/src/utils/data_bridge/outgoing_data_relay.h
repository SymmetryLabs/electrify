#pragma once

#include <memory>

#include "data_proxy.h"

class EventQueue;

class OutgoingDataRelay {

public:
    OutgoingDataRelay() = default;
    explicit OutgoingDataRelay(const std::shared_ptr<EventQueue>& queue);

    bool commitTransaction(unsigned int id = 0, bool forceTransaction = false);

    DataProxy& getProxy();

private:
    std::shared_ptr<EventQueue> queue;

    DataProxy dataProxy;

};
