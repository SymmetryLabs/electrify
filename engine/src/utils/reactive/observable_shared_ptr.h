#pragma once

#include <memory>
#include <utility>

#include "var.h"

template <typename T>
class ObservableSharedPtr : public Var<std::shared_ptr<T>> {

public:
    typedef typename std::shared_ptr<T>::element_type element_type;

    constexpr ObservableSharedPtr() noexcept {}
    constexpr ObservableSharedPtr(std::nullptr_t n) : Var<std::shared_ptr<T>>{std::shared_ptr<T>{n}} {}
    template <typename U>
    explicit ObservableSharedPtr(U* p) : Var<std::shared_ptr<T>>{std::shared_ptr<T>{p}} {}
    ObservableSharedPtr(const std::shared_ptr<T>& x) noexcept : Var<std::shared_ptr<T>>{std::shared_ptr<T>{x}} {}
    template <typename U>
    ObservableSharedPtr(const std::shared_ptr<U>& x) noexcept : Var<std::shared_ptr<T>>{std::shared_ptr<T>{x}} {}
    template <typename U>
    explicit ObservableSharedPtr(const std::weak_ptr<U>& x) : Var<std::shared_ptr<T>>{std::shared_ptr<T>{x}} {}
    ObservableSharedPtr(std::shared_ptr<T>&& x) noexcept : Var<std::shared_ptr<T>>{std::shared_ptr<T>{std::forward<std::shared_ptr<T>>(x)}} {}
    template <typename U>
    ObservableSharedPtr(std::shared_ptr<U>&& x) noexcept : Var<std::shared_ptr<T>>{std::shared_ptr<T>{std::forward<std::shared_ptr<T>>(x)}} {}
    template <typename U, typename D>
    ObservableSharedPtr(std::unique_ptr<U, D>&& x) : Var<std::shared_ptr<T>>{std::shared_ptr<T>{std::forward<std::unique_ptr<T>>(x)}} {}

    ~ObservableSharedPtr();

    ObservableSharedPtr& operator=(const std::shared_ptr<T>& x) noexcept;
    template <typename U>
    ObservableSharedPtr& operator=(const std::shared_ptr<U>& x) noexcept;
    ObservableSharedPtr& operator=(std::shared_ptr<T>&& x) noexcept;
    template <typename U>
    ObservableSharedPtr& operator=(std::shared_ptr<U>&& x) noexcept;
    template <typename U, typename D>
    ObservableSharedPtr& operator=(std::unique_ptr<U, D>&& x);

    void swap(std::shared_ptr<T>& x) noexcept;

    void reset() noexcept;
    template <typename U>
    void reset(U* p);
    template <typename U, typename D>
    void reset(U* p, D del);
    template <typename U, typename D, typename Alloc>
    void reset(U* p, D del, Alloc alloc);

    element_type* get() const noexcept { return this->getValue().get(); }
    element_type& operator*() const noexcept { return this->getValue().operator*(); }
    element_type* operator->() const noexcept { return this->getValue().operator->(); }

    long int use_count() const noexcept { return this->getValue().use_count(); }

    explicit operator bool() const noexcept { return this->getValue().operator bool(); }

    template <typename U> bool owner_before(const std::shared_ptr<U>& x) const { return this->getValue().owner_before(x); }
    template <typename U> bool owner_before(const std::weak_ptr<U>& x) const { return this->getValue().owner_before(x); }

private:
    template<typename t>
    friend std::ostream &operator<<(std::ostream& os, const ObservableSharedPtr<t>& osp);

    template<typename Archive, typename t>
    friend void serialize(Archive& archive, ObservableSharedPtr<t>& osp);

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ObservableSharedPtr<T>& osp) { 
    return os << osp.getValue();
}

#include "observable_shared_ptr.hpp"
