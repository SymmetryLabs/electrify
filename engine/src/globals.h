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

#include <prettyprint.hpp>

using namespace std;
using namespace chrono;

#include "cpp_ext.h"
#include "stl_ext.h"
#include "reactive.h"
#include "misc_utils.h"
#include "type_erasure.h"

#define printFunction std::cout << __PRETTY_FUNCTION__ << std::endl;
