#pragma once

#include <boost/uuid/uuid.hpp>

#include "event_queue.h"
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

    EventQueue masterQueue;
    EventQueue slaveQueue;

    DataRelay masterRelay;
    DataRelay slaveRelay;

    DataProxy masterProxy;
    DataProxy slaveProxy;

};
