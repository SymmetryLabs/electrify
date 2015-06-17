cmake_minimum_required (VERSION 2.6)
project (SymmetryEngine)

file(GLOB HEADERS
  src
  src/components
  src/components/oscillators
)
include_directories(${HEADERS})

file(GLOB_RECURSE SRCS
  "src/*.cpp"
  "libs/jsoncpp/*.cpp"
)
include_directories("libs/jsoncpp")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(SymmetryEngine SHARED ${SRCS})
source_group("src" FILES ${SRCS})
