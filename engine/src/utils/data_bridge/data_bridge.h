#pragma once

#include <boost/uuid/uuid.hpp>

#include "event_queue.h"
#include "data_relay.h"

class DataBridge {

public:
    DataBridge();

    boost::uuids::uuid uuid;

    DataRelay& getMasterRelay();
    DataRelay& getSlaveRelay();

    void flushAll();

private:

    EventQueue masterQueue;
    EventQueue slaveQueue;

    DataRelay masterRelay;
    DataRelay slaveRelay;

};
