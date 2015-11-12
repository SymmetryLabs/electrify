#pragma once

#include <memory>
#include <utility>

#include "type_traits_ext.h"

// Reference implementation:
//   https://github.com/USCiLab/cereal/blob/v1.1.2/include/cereal/types/memory.hpp#L117
template <typename T, typename Enable = void>
class EnabledSharedFromThisStatePreserver {
public:
    explicit EnabledSharedFromThisStatePreserver(T* ptr) {}
};

template <typename T>
class EnabledSharedFromThisStatePreserver<T, void_t<decltype(std::declval<T>().shared_from_this())>> {

    using EnableSharedFromThisTemplateType = typename decltype(std::declval<T>().shared_from_this())::element_type;
    using EnableSharedFromThisType = std::enable_shared_from_this<EnableSharedFromThisTemplateType>;

public:
    explicit EnabledSharedFromThisStatePreserver(T* ptr)
    : basePtr(static_cast<EnableSharedFromThisType*>(ptr))
    , state()
    {
        std::memcpy(&state, basePtr, sizeof(EnableSharedFromThisType));
    }

    ~EnabledSharedFromThisStatePreserver()
    {
      std::memcpy(basePtr, &state, sizeof(EnableSharedFromThisType));
    }

private:
    EnableSharedFromThisType* basePtr = nullptr;
    typename std::aligned_storage<sizeof(EnableSharedFromThisType)>::type state;
};

// Breaks the creation of shared_ptr into 2 phases.
// (1) Accepts a callback that gives access to the initialized shared_ptr
//   which points to the uninitialized but alloc'd object.
// (2) The inner object is constructed/initialized.
//
// Useful for things like caching with circular references.
// Handles inheriting from std::enable_shared_from_this<> by saving the
//   state of the std::enable_shared_from_this<> base class and restoring
//   after the object's constructor has returned.
// Uses "placement new" to initialize the alloc'd memory.
//
// Reference implementation:
//   https://github.com/USCiLab/cereal/blob/v1.1.2/include/cereal/types/memory.hpp#L250
// See:
//   https://github.com/USCiLab/cereal/issues/47
template <typename T, typename... Args>
std::shared_ptr<T> allocSharedPtr(std::function<void(std::shared_ptr<T>)> preConstruction, Args&&... ctorArgs)
{
    using StorageType = typename std::aligned_storage<sizeof(T)>::type;

    std::shared_ptr<T> ptr;
    auto initialized = std::make_shared<bool>(false);

    ptr.reset(reinterpret_cast<T*>(new StorageType()), [initialized] (T* t) {
        if (*initialized) {
            t->~T();
        }
        delete reinterpret_cast<StorageType*>(t);
    });

    preConstruction(ptr);
    {
        auto statePreserver = EnabledSharedFromThisStatePreserver<T>(ptr.get());
        new (ptr.get()) T(std::forward<Args>(ctorArgs)...);
        (void)statePreserver; // suppress unused warning
    }
    *initialized = true;

    return ptr;
}
