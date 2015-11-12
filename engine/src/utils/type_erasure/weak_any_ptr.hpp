template <typename ValueType>
WeakAnyPtr::WeakAnyPtr(const std::shared_ptr<ValueType>& value_)
: weakPtr(value_)
, anyPtr(*value_)
{
}

template <typename T>
std::shared_ptr<T> WeakAnyPtr::get() const
{
    return lock().get<T>();
}

template <typename T>
std::shared_ptr<T> SharedAnyPtr::get() const
{
    if (sharedPtr) {
        return {sharedPtr, anyPtr.get<T>()};
    }
    return {};
}
