template <typename ValueType>
AnyPtr::AnyPtr(ValueType& value_)
: typeErasure(eraseType(value_))
{
}

template <typename T>
T* AnyPtr::get() const
{
    return typeErasure->get<T>();
}
