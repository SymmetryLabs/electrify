cmake_minimum_required (VERSION 2.6)
project (testapp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable (testapp app.cpp app.h)
source_group("src" FILES app.cpp app.h)

target_link_libraries (testapp SymmetryEngine)
include_directories ("${PROJECT_SOURCE_DIR}/../engine/src")
include_directories ("${PROJECT_SOURCE_DIR}/../engine/libs/jsoncpp")
