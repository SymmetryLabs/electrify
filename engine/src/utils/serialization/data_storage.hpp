template <typename T>
void DataStorage::setValue(KeyType key, T value)
{
    setVariant(key, value);
}

template <typename T>
T DataStorage::getValue(KeyType key, T defaultValue)
{
    if (hasValue(key)) {
        return boost::get<T>(getVariant(key));
    } else {
        setValue(key, defaultValue);
        return defaultValue;
    }
}
