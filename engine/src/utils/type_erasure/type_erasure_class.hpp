template <typename T>
T* TypeErasure::get() const
{
    try { raise(); }
    catch (T* p) { return p; }
    catch (...) {}

    return nullptr;
}

template <typename T, bool = std::is_polymorphic<T>::value>
struct TypeErasureHelper;

template <typename T>
struct TypeErasureHelper<T, true> {
    static void raise(T& t) { t.raise(); }
};

template <typename T>
struct TypeErasureHelper<T, false> {
    static void raise(T& t) { throw &t; }
};

template <typename T>
class TypeErasureImpl : public TypeErasure {

public:
    explicit TypeErasureImpl(T& t_) : t(t_) {}

private:
    void raise() const { TypeErasureHelper<T>::raise(t); }

    T& t;

};

template <typename T>
std::shared_ptr<TypeErasure> eraseType(T& t)
{
    return std::make_shared<TypeErasureImpl<T>>(t);
}
