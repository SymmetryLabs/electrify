#pragma once

#include <memory>

namespace std {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

}

template<typename R, typename T,
    typename std::enable_if<std::is_convertible<T*, R*>::value, int>::type = 0>
std::unique_ptr<R> dynamic_unique_ptr_cast(std::unique_ptr<T>&& ptr)
{
    auto innerPtr = ptr.release();
    auto rPtr = dynamic_cast<R*>(innerPtr);
    auto r = std::unique_ptr<R>(rPtr);
    return std::move(r);
}

template<typename R, typename T,
    typename std::enable_if<!std::is_convertible<T*, R*>::value, int>::type = 0>
std::unique_ptr<R> dynamic_unique_ptr_cast(std::unique_ptr<T>&& ptr)
{
    return nullptr;
}
