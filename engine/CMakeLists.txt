cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (SymmetryEngine)

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

CPM_AddModule("libnoise"
 SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/libnoise"
 )

CPM_AddModule("jsoncpp"
 SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/jsoncpp"
 EXPORT_MODULE TRUE
 )

CPM_AddModule("CppReact"
 SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/CppReact"
 EXPORT_MODULE TRUE
 )

CPM_AddModule("cereal"
 SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/cereal"
 )

CPM_Finish()

find_package(Boost REQUIRED)

#------------------------------------------------------------------------------
# SymmetryEngine
#------------------------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (APPLE)
  set(CMAKE_MACOSX_RPATH ON)
endif()

file(GLOB HEADER_DIRS
  "src"
  "src/core"
  "src/blueprint"
  "src/blueprint_ui"
  "src/nodes"
  "src/nodes/oscillators"
  "src/nodes/transforms"
  "src/utils"
)

file(GLOB LIB_HEADER_DIRS
  "libs"
)

file(GLOB_RECURSE SRCS
  "src/*.cpp"
  "src/*.h"
  "src/*.tpp"
  "libs/FastLED/*.cpp"
  "libs/FastLED/*.h"
)
source_group("src" FILES ${SRCS})

include_directories(SYSTEM ${CPM_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${LIB_HEADER_DIRS})
include_directories(${HEADER_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(SymmetryEngine STATIC ${SRCS})

target_include_directories(SymmetryEngine SYSTEM PUBLIC ${CPM_INCLUDE_DIRS})
target_include_directories(SymmetryEngine SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(SymmetryEngine SYSTEM PUBLIC ${LIB_HEADER_DIRS})
target_include_directories(SymmetryEngine PUBLIC ${HEADER_DIRS})

target_link_libraries(SymmetryEngine PUBLIC ${CPM_LIBRARIES})

foreach(subdir ${LIB_HEADER_DIRS} ${CPM_INCLUDE_DIRS})
  file(GLOB temp ${subdir}/*)
  set(EXPORT_HEADERS ${EXPORT_HEADERS} ${temp})
endforeach()

file(COPY ${EXPORT_HEADERS} DESTINATION ext_include FILES_MATCHING PATTERN *.h PATTERN *.tpp PATTERN *.hpp)
