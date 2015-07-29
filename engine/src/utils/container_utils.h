#pragma once
#include "globals.h"

template<typename T, typename C>
unique_ptr<T> removeUniquePtr(C& container, T* value)
{
  auto valueIter = find_if(container.begin(), container.end(),
    [&] (const std::unique_ptr<T>& p) {
      return p.get() == value;
    });
  auto valuePtr = move(*valueIter);
  container.erase(valueIter);
  return valuePtr;
}

template<typename T, typename C>
shared_ptr<T> removeSharedPtr(C& container, T* value)
{
  auto valueIter = find_if(container.begin(), container.end(),
    [&] (const std::shared_ptr<T>& p) {
      return p.get() == value;
    });
  auto valuePtr = move(*valueIter);
  container.erase(valueIter);
  return valuePtr;
}
