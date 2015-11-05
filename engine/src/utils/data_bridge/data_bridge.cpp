#include "data_bridge.h"

#include <boost/uuid/random_generator.hpp>
#include "event_queue.h"

DataBridge::DataBridge()
: masterQueue(std::make_shared<EventQueue>())
, slaveQueue(std::make_shared<EventQueue>())
, masterRelay(masterQueue, slaveQueue)
, slaveRelay(slaveQueue, masterQueue)
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
    return masterRelay.getProxy();
}

DataProxy& DataBridge::getSlaveProxy()
{
    return slaveRelay.getProxy();
}

void DataBridge::flushAll()
{
    masterRelay.commitOutgoingTransaction();
    slaveRelay.commitOutgoingTransaction();
    masterRelay.processIncomingTransactions();
    slaveRelay.processIncomingTransactions();
}
