template <typename T>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(const std::shared_ptr<T>& x) noexcept
{
    notifyWillRemove();
    sp.operator=(x);
    notifyDidAdd();
    return *this;
}

template <typename T>
template <typename U>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(const std::shared_ptr<U>& x) noexcept
{
    notifyWillRemove();
    sp.operator=(x);
    notifyDidAdd();
    return *this;
}

template <typename T>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::shared_ptr<T>&& x) noexcept
{
    notifyWillRemove();
    sp.operator=(std::forward<std::shared_ptr<T>>(x));
    notifyDidAdd();
    return *this;
}

template <typename T>
template <typename U>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::shared_ptr<U>&& x) noexcept
{
    notifyWillRemove();
    sp.operator=(std::forward<std::shared_ptr<T>>(x));
    notifyDidAdd();
    return *this;
}

template <typename T>
template <typename U, typename D>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::unique_ptr<U, D>&& x)
{
    notifyWillRemove();
    sp.operator=(std::forward<std::shared_ptr<T>>(x));
    notifyDidAdd();
    return *this;
}

template <typename T>
void ObservableSharedPtr<T>::swap(std::shared_ptr<T>& x) noexcept
{
    notifyWillRemove();
    sp.operator=(x);
    notifyDidAdd();
}

template <typename T>
void ObservableSharedPtr<T>::reset() noexcept
{
    notifyWillRemove();
    sp.reset();
}

template <typename T>
template <typename U>
void ObservableSharedPtr<T>::reset(U* p)
{
    notifyWillRemove();
    sp.reset(p);
    notifyDidAdd();
}

template <typename T>
template <typename U, typename D>
void ObservableSharedPtr<T>::reset(U* p, D del)
{
    notifyWillRemove();
    sp.reset(p, del);
    notifyDidAdd();
}

template <typename T>
template <typename U, typename D, typename Alloc>
void ObservableSharedPtr<T>::reset(U* p, D del, Alloc alloc)
{
    notifyWillRemove();
    sp.reset(p, del, alloc);
    notifyDidAdd();
}

template <typename T>
void ObservableSharedPtr<T>::notifyWillRemove() const
{
    if (sp) {
        willRemoveValue.emit(sp.get());
    }
}

template <typename T>
void ObservableSharedPtr<T>::notifyDidAdd() const
{
    if (sp) {
        didAddValue.emit(sp.get());
    }
}

