#pragma once

#include <memory>

#include <boost/uuid/uuid.hpp>

#include "data_relay.h"
#include "data_proxy.h"

class DataBridge {

public:
    DataBridge();

    boost::uuids::uuid uuid;

    DataRelay& getMasterRelay();
    DataRelay& getSlaveRelay();

    DataProxy& getMasterProxy();
    DataProxy& getSlaveProxy();

    void flushAll();

private:

    std::shared_ptr<EventQueue> masterQueue;
    std::shared_ptr<EventQueue> slaveQueue;

    DataRelay masterRelay;
    DataRelay slaveRelay;

    DataProxy masterProxy;
    DataProxy slaveProxy;

};
