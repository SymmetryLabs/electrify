#include "data_storage.h"

bool DataStorage::hasValue(KeyType key)
{
    return storage.find(key) != storage.end();
}

void DataStorage::setVariant(KeyType key, ValueType value)
{
    storage[key] = value;
}

DataStorage::ValueType DataStorage::getVariant(KeyType key)
{
    return storage[key];
}
