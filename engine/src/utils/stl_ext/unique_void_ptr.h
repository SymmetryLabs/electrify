#pragma once

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

class UniqueVoidPtr : private boost::noncopyable {

public:
    template <typename T>
    explicit UniqueVoidPtr(T* ptr);
    template <typename T>
    explicit UniqueVoidPtr(std::unique_ptr<T>&& ptr);

    void reset();

private:
    std::shared_ptr<void> ptr;

};

#include "unique_void_ptr.hpp"
