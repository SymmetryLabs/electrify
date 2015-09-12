#include "data_transmitter.h"

DataTransmitter::DataTransmitter(const std::weak_ptr<void>& destination_)
: destination(destination_)
{
}

void DataTransmitter::setDestination(const std::weak_ptr<void>& destination_)
{
    destination = destination_;
}

void DataTransmitter::setDataRelays(DataRelay& masterDataRelay_, DataRelay& slaveDataRelay_)
{
    masterDataRelay = &masterDataRelay_;
    slaveDataRelay = &slaveDataRelay_;
}

void DataTransmitter::sendFunction(const std::function<void()>& fn)
{
    if (masterDataRelay) {
        masterDataRelay->queueEvent(fn);
    } else {
        fn();
    }
}
