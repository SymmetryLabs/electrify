#pragma once

#include <memory>

template <typename R, typename T>
std::shared_ptr<R> shared_from_this(std::enable_shared_from_this<T>& ptr)
{
    return std::dynamic_pointer_cast<R>(ptr.shared_from_this());
}

template <typename R, typename T>
std::shared_ptr<R const> shared_from_this(const std::enable_shared_from_this<T>& ptr)
{
    return std::dynamic_pointer_cast<R const>(ptr.shared_from_this());
}
