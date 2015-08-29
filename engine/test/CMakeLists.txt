cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (NOT TARGET SymmetryEngine)
  add_subdirectory(".." "${CMAKE_CURRENT_BINARY_DIR}/engine")
endif()

file(GLOB_RECURSE TEST_SOURCES
  "*.cpp"
  "*.h"
  "*.tpp"
  "*.hpp"
)
source_group("src" FILES ${TEST_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SymmetryEngine_test ${TEST_SOURCES})
target_link_libraries(SymmetryEngine_test SymmetryEngine)

add_test(NAME tests COMMAND SymmetryEngine_test -r console)
