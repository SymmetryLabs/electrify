#pragma once

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include "unique_void_ptr.h"

class ScopedPtr {

public:
    template <typename T>
    explicit ScopedPtr(T* ptr);
    template <typename T>
    explicit ScopedPtr(std::unique_ptr<T>&& ptr);

    void release();

    /*
     * forking creates another ScopedPtr such that
     * if either the original or the fork (or copies therein)
     * go out of scope, the subject object is released.
     */
    ScopedPtr fork() const;

private:
    struct ScopedPtrContainer {
        template <typename T>
        explicit ScopedPtrContainer(T* ptr);
        template <typename T>
        explicit ScopedPtrContainer(std::unique_ptr<T>&& ptr);
        explicit ScopedPtrContainer(const std::shared_ptr<UniqueVoidPtr>& ptr);
        ~ScopedPtrContainer();
        void release();
        std::shared_ptr<UniqueVoidPtr> ptr;
    };

    ScopedPtr(const std::shared_ptr<UniqueVoidPtr>& gatekeeper);

    std::shared_ptr<ScopedPtrContainer> container;

};

template<typename T, typename... Args>
ScopedPtr make_scoped_ptr(Args&&... args)
{
    return ScopedPtr{new T{std::forward<Args>(args)...}};
}

#include "scoped_ptr.hpp"
