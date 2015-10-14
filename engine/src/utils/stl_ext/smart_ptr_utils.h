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
    return {std::move(ptr)};
}

template<typename R, typename T,
    typename std::enable_if<!std::is_convertible<T*, R*>::value, int>::type = 0>
std::unique_ptr<R> dynamic_unique_ptr_cast(std::unique_ptr<T>&& ptr)
{
    if (auto ptrConverted = dynamic_cast<R*>(ptr.get())) {
        ptr.release();
        return {ptrConverted};
    }
    return nullptr;
}