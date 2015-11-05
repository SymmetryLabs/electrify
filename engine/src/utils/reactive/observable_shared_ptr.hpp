template <typename T>
ObservableSharedPtr<T>::~ObservableSharedPtr()
{
    ObjectOwner::releaseAll();
}

template <typename T>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(const std::shared_ptr<T>& x) noexcept
{
    this->emit(x);
    return *this;
}

template <typename T>
template <typename U>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(const std::shared_ptr<U>& x) noexcept
{
    this->emit(x);
    return *this;
}

template <typename T>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::shared_ptr<T>&& x) noexcept
{
    this->emit(std::forward<std::shared_ptr<T>>(x));
    return *this;
}

template <typename T>
template <typename U>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::shared_ptr<U>&& x) noexcept
{
    this->emit(std::forward<std::shared_ptr<U>>(x));
    return *this;
}

template <typename T>
template <typename U, typename D>
ObservableSharedPtr<T>& ObservableSharedPtr<T>::operator=(std::unique_ptr<U, D>&& x)
{
    this->emit(std::forward<std::unique_ptr<U, D>>(x));
    return *this;
}

template <typename T>
void ObservableSharedPtr<T>::swap(std::shared_ptr<T>& x) noexcept
{
    auto val = this->getValue();
    val.swap(x);
    this->emit(val);
}

template <typename T>
void ObservableSharedPtr<T>::reset() noexcept
{
    this->emit(nullptr);
}

template <typename T>
template <typename U>
void ObservableSharedPtr<T>::reset(U* p)
{
    this->emit(std::shared_ptr<U>{p});
}

template <typename T>
template <typename U, typename D>
void ObservableSharedPtr<T>::reset(U* p, D del)
{
    this->emit(std::shared_ptr<U>{p, del});
}

template <typename T>
template <typename U, typename D, typename Alloc>
void ObservableSharedPtr<T>::reset(U* p, D del, Alloc alloc)
{
    this->emit(std::shared_ptr<U>{p, alloc});
}
