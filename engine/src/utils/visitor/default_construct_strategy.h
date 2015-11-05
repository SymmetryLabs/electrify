#pragma once

#include <memory>
#include <iostream>

#include "visitor_base.h"

class DefaultConstructStrategy : public VisitorBase<DefaultConstructStrategy> {
};

template <typename T>
T performOnObjects(DefaultConstructStrategy&, T&)
{
    return {};
}

template <typename T>
T performOnObjects(DefaultConstructStrategy&, const T&)
{
    return {};
}

template <typename T>
std::shared_ptr<T> performOnObjects(DefaultConstructStrategy&, T* t)
{
    if (t) {
        return std::make_shared<T>();
    } else {
        return {};
    }
}

template <typename T>
std::shared_ptr<T> performOnObjects(DefaultConstructStrategy&, const T* t)
{
    if (t) {
        return std::make_shared<T>();
    } else {
        return {};
    }
}

template <typename T>
std::shared_ptr<T> performOnObjects(DefaultConstructStrategy&, std::shared_ptr<T>& t)
{
    if (t) {
        return std::make_shared<T>();
    } else {
        return {};
    }
}

template <typename T>
std::shared_ptr<T> performOnObjects(DefaultConstructStrategy&, const std::shared_ptr<T>& t)
{
    if (t) {
        return std::make_shared<T>();
    } else {
        return {};
    }
}
