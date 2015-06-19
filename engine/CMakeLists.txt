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

CPM_Finish()

find_package(Boost REQUIRED)

#------------------------------------------------------------------------------
# SymmetryEngine
#------------------------------------------------------------------------------

project(SymmetryEngine)

file(GLOB HEADERS
  "src"
  "src/components"
  "src/components/oscillators"
  "libs"
)

file(GLOB_RECURSE SRCS
  "src/*.cpp"
  "libs/FastLED/*.cpp"
)
source_group("src" FILES ${SRCS})

include_directories(${Boost_INCLUDE_DIRS} ${HEADERS} ${CPM_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(SymmetryEngine SHARED ${SRCS})
target_include_directories(SymmetryEngine PUBLIC ${Boost_INCLUDE_DIRS} ${HEADERS} ${CPM_INCLUDE_DIRS})

target_link_libraries(SymmetryEngine ${CPM_LIBRARIES})

foreach(subdir ${HEADERS} ${CPM_INCLUDE_DIRS})
  file(GLOB temp ${subdir}/*)
  set(EXPORT_HEADERS ${EXPORT_HEADERS} ${temp})
endforeach()

file(COPY ${EXPORT_HEADERS} DESTINATION include FILES_MATCHING PATTERN *.h PATTERN *.tpp)
