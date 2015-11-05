#pragma once

#include <type_traits>
#include <utility>

#include "type_traits_ext.h"

template <typename...>
static std::false_type CheckMemberPerformOnObjects(...);
template <typename T, typename... Args>
static auto CheckMemberPerformOnObjects(T&& t, Args&&... args)
    -> typename Check<decltype(std::forward<T>(t).performOnObjects(std::forward<Args>(args)...))>::type;

template <typename...>
static std::false_type CheckNonMemberPerformOnObjects(...);
template <typename... Args>
static auto CheckNonMemberPerformOnObjects(Args&&... args)
    -> typename Check<decltype(performOnObjects(std::forward<Args>(args)...))>::type;

template <typename...>
static std::false_type CheckStaticMemberPerformOnObjects(...);
template <typename T, typename... Args>
static auto CheckStaticMemberPerformOnObjects(Args&&... args)
    -> typename Check<decltype(T::performOnObjects(std::forward<Args>(args)...))>::type;

template <typename Visitor>
class VisitorBase {

public:
    virtual ~VisitorBase() = default;

    template <typename T, typename... Args>
    auto operator()(T&& t, Args&&... args)
        -> decltype(t.performOnObjects(std::declval<Visitor&>(), std::forward<Args>(args)...))
    {
        return t.performOnObjects(dynamic_cast<Visitor&>(*this), std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    auto operator()(T&& t, Args&&... args)
        -> typename std::enable_if<!decltype(CheckMemberPerformOnObjects(std::forward<T>(t), std::declval<Visitor&>(), std::forward<Args>(args)...))::value,
            decltype(performOnObjects(std::declval<Visitor&>(), std::forward<T>(t), std::forward<Args>(args)...))>::type
    {
        return performOnObjects(dynamic_cast<Visitor&>(*this), std::forward<T>(t), std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    auto operator()(T&& t, Args&&... args)
        -> typename std::enable_if<decltype(CheckMemberPerformOnObjects(std::declval<Visitor&>(), std::forward<T>(t), std::forward<Args>(args)...))::value
            && !decltype(CheckNonMemberPerformOnObjects(std::declval<Visitor&>(), std::forward<T>(t), std::forward<Args>(args)...))::value
            && !decltype(CheckMemberPerformOnObjects(std::forward<T>(t), std::declval<Visitor&>(), std::forward<Args>(args)...))::value>::type
    {
        return dynamic_cast<Visitor&>(*this).performOnObjects(std::forward<T>(t), std::forward<Args>(args)...);
    }

};

// template <typename Visitor, template <typename> class... SharedPtrType, typename T,
//     typename enable_if_all<int, are_same<std::shared_ptr<T>, typename std::decay<SharedPtrType<T>>::type...>::value>::type = 0>
// auto performOnObjects(Visitor&& visitor, SharedPtrType<T>&&... t)
//     -> decltype(visitor((*t)...))
// {
//     if (bool_and<t...>::value) {
//         return visitor((*t)...);
//     }
// }
