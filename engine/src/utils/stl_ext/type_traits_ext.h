#pragma once

#include <type_traits>

// See: http://en.cppreference.com/w/cpp/types/void_t
template<typename> using void_t = void;

template<typename T, typename S>
struct has_return_type {
    typedef S type;
};

template<typename T>
struct has_return_type<T, typename T::return_type> {
};

template<typename T, typename A0, typename = void>
struct is_callable : std::false_type {
};

template<typename T, typename A0>
struct is_callable<T, A0, void_t<decltype( std::declval<T>()(std::declval<A0>()) )>> : std::true_type {
};
