cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# See: https://cmake.org/pipermail/cmake/2012-June/050674.html
MACRO(HEADER_DIRECTORIES list)
    SET(dir_list "")
    FOREACH(file_path ${${list}})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${list} ${dir_list})
ENDMACRO()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

if (NOT TARGET SymmetryEngine)
    add_subdirectory(".." "${CMAKE_CURRENT_BINARY_DIR}/engine")
endif()

file(GLOB_RECURSE TEST_SOURCES
    "test.cpp"
    "tests/*.cpp"
    "tests/*.h"
    "tests/*.tpp"
    "tests/*.hpp"
    "test_data/*.h"
    "test_data/*.cpp"
)
source_group("src" FILES ${TEST_SOURCES})

file(GLOB_RECURSE TEST_HEADERS
    "tests/*.h"
    "tests/*.tpp"
    "tests/*.hpp"
    "test_data/*.h"
)
HEADER_DIRECTORIES(TEST_HEADERS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${TEST_HEADERS})

add_executable(SymmetryEngine_test ${TEST_SOURCES})
target_link_libraries(SymmetryEngine_test SymmetryEngine)

add_test(NAME tests COMMAND SymmetryEngine_test -r console)
