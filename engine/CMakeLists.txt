cmake_minimum_required (VERSION 2.6)
project (SymmetryEngine)
file(GLOB SRCS
    "src/*.h"
    "src/*.cpp"
    "libs/jsoncpp/*.cpp"
)
include_directories("libs/jsoncpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(SymmetryEngine SHARED ${SRCS})
source_group("src" FILES ${SRCS})
