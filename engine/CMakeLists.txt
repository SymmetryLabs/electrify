cmake_minimum_required (VERSION 2.6)

#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
  message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
    RESULT_VARIABLE error_code
    OUTPUT_QUIET ERROR_QUIET)
  if(error_code)
    message(FATAL_ERROR "CPM failed to get the hash for HEAD")
  endif()
endif()
include(${CPM_DIR}/CPM.cmake)

#------------------------------------------------------------------------------
# CPM Modules
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# SymmetryEngine
#------------------------------------------------------------------------------

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
  "libs/FastLED/*.cpp"
)
include_directories("libs/jsoncpp")
include_directories("libs/FastLED")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(SymmetryEngine ${CPM_LIBRARIES}) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(SymmetryEngine SHARED ${SRCS})
source_group("src" FILES ${SRCS})
