#pragma once

#include <memory>

struct virtual_enable_shared_from_this_base :
    std::enable_shared_from_this<virtual_enable_shared_from_this_base>
{
    virtual ~virtual_enable_shared_from_this_base() = default;
};

struct virtual_enable_shared_from_this : virtual virtual_enable_shared_from_this_base {
    virtual ~virtual_enable_shared_from_this() = default;
};
