#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

using namespace std;
using namespace chrono;

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}
