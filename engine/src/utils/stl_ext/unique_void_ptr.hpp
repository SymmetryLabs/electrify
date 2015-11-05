template <typename T>
UniqueVoidPtr::UniqueVoidPtr(T* ptr_)
: ptr(std::shared_ptr<T>{ptr_})
{
}

template <typename T>
UniqueVoidPtr::UniqueVoidPtr(std::unique_ptr<T>&& ptr_)
: ptr(std::move(ptr_))
{
}
