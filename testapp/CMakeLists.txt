cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (NOT TARGET SymmetryEngine)
  add_subdirectory("../engine" "${CMAKE_CURRENT_BINARY_DIR}/engine")
endif()

add_executable (testapp app.cpp)
source_group("src" FILES app.cpp app.h)

target_link_libraries(testapp SymmetryEngine)
