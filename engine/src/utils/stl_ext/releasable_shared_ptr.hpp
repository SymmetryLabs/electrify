template <typename T>
ReleasableSharedPtr<T>::ReleasableSharedPtr(std::unique_ptr<T>&& inPtr)
: released(std::make_shared<bool>(false))
{
    auto p = std::move(inPtr);
    ptr = std::shared_ptr<T>(p.release(),
        [this] (T* p) {
            if (!*released) {
                delete p;
            }
        }
    );
}

template <typename T>
std::unique_ptr<T> ReleasableSharedPtr<T>::release() const
{
    auto r = std::unique_ptr<T>(ptr.get());
    *released = true;
    return std::move(r);
}
