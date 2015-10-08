template <typename T>
T* TypeErasure::get() const
{
    try { raise(); }
    catch (T* p) { return p; }
    catch (...) {}

    return nullptr;
}

template <typename T>
class TypeErasureImpl : public TypeErasure {

public:
    explicit TypeErasureImpl(T& t_) : t(t_) {}

private:
    void raise() const { t.raise(); }

    T& t;

};

template <typename T>
std::shared_ptr<TypeErasure> eraseType(T& t)
{
    return std::make_shared<TypeErasureImpl<T>>(t);
}
