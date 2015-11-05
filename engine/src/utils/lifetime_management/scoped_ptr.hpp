template <typename T>
ScopedPtr::ScopedPtr(T* ptr)
: container(std::make_shared<ScopedPtrContainer>(ptr))
{
}

template <typename T>
ScopedPtr::ScopedPtr(std::unique_ptr<T>&& ptr)
: container(std::make_shared<ScopedPtrContainer>(std::forward<std::unique_ptr<T>>(ptr)))
{
}

template <typename T>
ScopedPtr::ScopedPtrContainer::ScopedPtrContainer(T* ptr_)
: ptr(std::make_shared<UniqueVoidPtr>(ptr_))
{
}

template <typename T>
ScopedPtr::ScopedPtrContainer::ScopedPtrContainer(std::unique_ptr<T>&& ptr_)
: ptr(std::make_shared<UniqueVoidPtr>(std::forward<std::unique_ptr<T>>(ptr_)))
{
}
