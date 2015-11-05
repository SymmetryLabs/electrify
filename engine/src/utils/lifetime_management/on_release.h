#pragma once

#include <functional>

class OnRelease {

public:
    template <typename F>
    explicit OnRelease(F&& releaseFunc);

    ~OnRelease();

private:
    std::function<void()> releaseFunc;

};

#include "on_release.hpp"
