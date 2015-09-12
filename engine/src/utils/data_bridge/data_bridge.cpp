#include "data_bridge.h"

#include <boost/uuid/random_generator.hpp>

DataBridge::DataBridge()
: masterRelay(masterQueue, slaveQueue)
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

void DataBridge::flushAll()
{
    masterRelay.commitOutgoingTransaction();
    slaveRelay.commitOutgoingTransaction();
    masterRelay.processIncomingTransactions();
    slaveRelay.processIncomingTransactions();
}
