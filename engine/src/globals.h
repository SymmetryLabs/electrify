#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>
#include <tuple>
#include <typeindex>
#include <vector>

#include "react/Domain.h"
#include "react/Signal.h"
#include "react/Event.h"

using namespace std;
using namespace chrono;
using namespace react;

#include "container_utils.h"

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

REACTIVE_DOMAIN(EngineDomain, sequential)
