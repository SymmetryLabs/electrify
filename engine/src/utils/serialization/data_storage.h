#pragma once
#include "globals.h"

#include <map>
#include <boost/variant.hpp>

class DataStorage {

public:
    typedef std::string KeyType;
    typedef boost::variant<int, long, float, double, std::string> ValueType;

    virtual ~DataStorage() = default;

    template <typename T>
    void setValue(KeyType key, T value);
    template <typename T>
    T getValue(KeyType key, T defaultValue = T());

private:
    std::map<std::string, ValueType> storage;

    bool hasValue(KeyType key);

    void setVariant(KeyType key, ValueType value);
    ValueType getVariant(KeyType key);

    template <typename Archive>
    friend void serialize(Archive& archive, DataStorage& ds);

};

#include "data_storage.hpp"
