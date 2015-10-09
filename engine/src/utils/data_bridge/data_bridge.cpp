#include "data_bridge.h"

#include <boost/uuid/random_generator.hpp>
#include "event_queue.h"

DataBridge::DataBridge()
: masterQueue(std::make_shared<EventQueue>())
, slaveQueue(std::make_shared<EventQueue>())
, masterRelay(*masterQueue, *slaveQueue)
, slaveRelay(*slaveQueue, *masterQueue)
, masterProxy(masterQueue)
, slaveProxy(slaveQueue)
{
    static boost::uuids::random_generator nodeUuidGenerator;
    uuid = nodeUuidGenerator();
}

DataRelay& DataBridge::getMasterRelay()
{
    return masterRelay;
}

DataRelay& DataBridge::getSlaveRelay()
{
    return slaveRelay;
}

DataProxy& DataBridge::getMasterProxy()
{
    return masterProxy;
}

DataProxy& DataBridge::getSlaveProxy()
{
    return slaveProxy;
}

void DataBridge::flushAll()
{
    masterRelay.commitOutgoingTransaction();
    slaveRelay.commitOutgoingTransaction();
    masterRelay.processIncomingTransactions();
    slaveRelay.processIncomingTransactions();
}
