#pragma once

#include <boost/utility.hpp>

template<typename T>
struct Singleton : private boost::noncopyable {
    static T& getInstance() {
        static T instance;
        return instance;
    }
};
