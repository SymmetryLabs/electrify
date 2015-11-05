template <typename T>
ScopedPtr ObjectOwner::retain(std::unique_ptr<T>&& ptr)
{
    auto scopedPtr = ScopedPtr{std::forward<std::unique_ptr<T>>(ptr)};
    objects.push_back(scopedPtr);
    return scopedPtr;
}
