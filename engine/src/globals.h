#pragma once

#include <cassert>
#include <chrono>
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <typeindex>
#include <vector>

#include <prettyprint.hpp>

using namespace std;
using namespace chrono;

#include "cpp_ext.h"
#include "stl_ext.h"

#include "reactive.h"
#include "lifetime_management.h"
#include "misc_utils.h"
#include "type_erasure.h"

#define printFunction std::cout << __PRETTY_FUNCTION__ << std::endl;
