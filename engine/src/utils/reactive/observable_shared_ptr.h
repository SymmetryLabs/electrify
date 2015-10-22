#pragma once

#include <memory>

#include "event.h"
#include "observes.h"

template <typename T>
class ObservableSharedPtr : public Observes {

public:
    typedef typename std::shared_ptr<T>::element_type element_type;

    Event<T*> didAddValue;
    Event<T*> willRemoveValue;

    constexpr ObservableSharedPtr() noexcept {}
    constexpr ObservableSharedPtr(std::nullptr_t n) : sp(n) {}
    template <typename U>
    explicit ObservableSharedPtr(U* p) : sp(p) {}
    ObservableSharedPtr(const std::shared_ptr<T>& x) noexcept : sp(x) {}
    template <typename U>
    ObservableSharedPtr(const std::shared_ptr<U>& x) noexcept : sp(x) {}
    template <typename U>
    explicit ObservableSharedPtr(const std::weak_ptr<U>& x) : sp(x) {}
    ObservableSharedPtr(std::shared_ptr<T>&& x) noexcept : sp(std::forward<std::shared_ptr<T>>(x)) {}
    template <typename U>
    ObservableSharedPtr(std::shared_ptr<U>&& x) noexcept : sp(std::forward<std::shared_ptr<T>>(x)) {}
    template <typename U, typename D>
    ObservableSharedPtr(std::unique_ptr<U, D>&& x) : sp(std::forward<std::shared_ptr<T>>(x)) {}

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

    element_type* get() const noexcept { return sp.get(); }
    element_type& operator*() const noexcept { return sp.operator*(); }
    element_type* operator->() const noexcept { return sp.operator->(); }

    long int use_count() const noexcept { return sp.use_count(); }

    explicit operator bool() const noexcept { return sp.operator bool(); }

    template <typename U> bool owner_before(const std::shared_ptr<U>& x) const { return sp.owner_before(x); }
    template <typename U> bool owner_before(const std::weak_ptr<U>& x) const { return sp.owner_before(x); }

private:
    std::shared_ptr<T> sp;

    void notifyWillRemove() const;
    void notifyDidAdd() const;

    template<typename t>
    friend std::ostream &operator<<(std::ostream& os, const ObservableSharedPtr<t>& osp);

    template<typename Archive, typename t>
    friend void serialize(Archive& archive, ObservableSharedPtr<t>& osp);

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ObservableSharedPtr<T>& osp) { 
    return os << osp.sp;
}

#include "observable_shared_ptr.hpp"
