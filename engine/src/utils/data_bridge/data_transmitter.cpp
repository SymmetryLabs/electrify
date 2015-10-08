#include "data_transmitter.h"

void DataTransmitter::setDataProxies(const DataProxy& masterDataProxy_, const DataProxy& slaveDataProxy_)
{
    masterDataProxy = masterDataProxy_;
    slaveDataProxy = slaveDataProxy_;
}
