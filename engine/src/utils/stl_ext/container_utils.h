#pragma once

#include <algorithm>
#include <memory>

template <typename T, typename C>
std::unique_ptr<T> removeUniquePtr(C& container, T* value)
{
    auto valueIter = std::find_if(container.begin(), container.end(),
        [&] (const std::unique_ptr<T>& p) {
            return p.get() == value;
        });
    auto valuePtr = std::move(*valueIter);
    container.erase(valueIter);
    return valuePtr;
}

template <typename T, typename C>
std::shared_ptr<T> removeSharedPtr(C& container, T* value)
{
    auto valueIter = std::find_if(container.begin(), container.end(),
        [&] (const std::shared_ptr<T>& p) {
            return p.get() == value;
        });
    auto valuePtr = std::move(*valueIter);
    container.erase(valueIter);
    return valuePtr;
}

template <typename T, typename C>
void removePtr(C& container, T* value)
{
    container.erase(std::remove(container.begin(), container.end(), value), container.end());
}
