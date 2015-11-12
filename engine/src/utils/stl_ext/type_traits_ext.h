#pragma once

#include <type_traits>

// See: http://en.cppreference.com/w/cpp/types/void_t
template <typename> using void_t = void;

// See: http://en.cppreference.com/w/cpp/language/type_alias
template <typename T> using Invoke = typename T::type;
template <typename Condition> using EnableIf =
    Invoke<std::enable_if<Condition::value>>;

template <typename T, typename S>
struct has_return_type {
    typedef S type;
};

template <typename T>
struct has_return_type<T, typename T::return_type> {
};

template <typename T, typename A0, typename = void>
struct is_callable : std::false_type {
};

template <typename T, typename A0>
struct is_callable<T, A0, void_t<decltype( std::declval<T>()(std::declval<A0>()) )>> : std::true_type {
};

template <typename T, typename Type = std::true_type>
struct Check {
    typedef Type type;
};


// See: http://stackoverflow.com/a/24687161/216311
template < bool... > struct bool_sequence {};

template < bool... Bs >
using bool_and = std::is_same< bool_sequence< Bs... >,
                               bool_sequence< ( Bs || true )... > >;

template < bool... Bs >
using bool_or = std::integral_constant< bool, !bool_and< !Bs... >::value >;

template < typename R, bool... Bs > // note: R first, no default :(
using enable_if_any = std::enable_if< bool_or< Bs... >::value, R >;

template < typename R, bool... Bs > // note: R first, no default :(
using enable_if_all = std::enable_if< bool_and< Bs... >::value, R >;

template < typename T, typename... Ts >
using are_same = bool_and< std::is_same< T, Ts >::value... >;
