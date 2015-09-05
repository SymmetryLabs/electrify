#pragma once

#include <memory>

struct virtual_enable_shared_from_this_base :
    std::enable_shared_from_this<virtual_enable_shared_from_this_base>
{
    virtual ~virtual_enable_shared_from_this_base() = default;
    template<typename T>
    std::shared_ptr<T> shared_from_this(T* thisPtr) {
        return std::dynamic_pointer_cast<T>(
            std::enable_shared_from_this<virtual_enable_shared_from_this_base>::shared_from_this());
    }
};

struct virtual_enable_shared_from_this : virtual virtual_enable_shared_from_this_base {
    virtual ~virtual_enable_shared_from_this() = default;
};
