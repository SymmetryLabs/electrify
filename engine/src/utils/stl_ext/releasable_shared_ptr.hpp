template <typename T>
ReleasableSharedPtr<T>::ReleasableSharedPtr(std::unique_ptr<T>&& inPtr)
: released(std::make_shared<bool>(false))
{
    auto localReleased = released;
    auto p = std::move(inPtr);
    ptr = std::shared_ptr<T>(p.release(),
        [=] (T* p) {
            if (!*localReleased) {
                delete p;
                *localReleased = true;
            }
        }
    );
}

template <typename T>
std::unique_ptr<T> ReleasableSharedPtr<T>::release() const
{
    if (!*released) {
        auto r = std::unique_ptr<T>(ptr.get());
        *released = true;
        return r;
    } else {
        return {};
    }
}
