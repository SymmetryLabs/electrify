cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#-----------------------------------------------------------------------
# CPM configuration
#-----------------------------------------------------------------------
set(CPM_MODULE_NAME CppReact)
set(CPM_LIB_TARGET_NAME ${CPM_MODULE_NAME})

if ((DEFINED CPM_DIR) AND (DEFINED CPM_UNIQUE_ID) AND (DEFINED CPM_TARGET_NAME))
  set(CPM_LIB_TARGET_NAME ${CPM_MODULE_NAME})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CPM_DIR})
  include(CPM)
else()
  set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
  find_package(Git)
  if(NOT GIT_FOUND)
    message(FATAL_ERROR "CPM requires Git.")
  endif()
  if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
      RESULT_VARIABLE error_code
      OUTPUT_VARIABLE head_sha)
    if(error_code)
      message(FATAL_ERROR "CPM failed to get the hash for HEAD")
    endif()
  endif()
  include(${CPM_DIR}/CPM.cmake)
endif()

# All externals *must* define this.
CPM_ForceOnlyOneModuleVersion()

CPM_InitModule(${CPM_MODULE_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(TBB REQUIRED)
include_directories(SYSTEM ${TBB_INCLUDE_DIRS})
find_library(TBB_LIB_PATH tbb)
add_library(tbb SHARED IMPORTED)
set_property(TARGET tbb PROPERTY IMPORTED_LOCATION ${TBB_LIB_PATH})

#------------------------------------------------------------------------------
# CppReact
#------------------------------------------------------------------------------

# Download source code
set(REPO_SOURCE_DIR "${CMAKE_BINARY_DIR}/${__CPM_FULL_UNID}/repo")
CPM_EnsureRepoIsCurrent(
  TARGET_DIR ${REPO_SOURCE_DIR}
  GIT_REPOSITORY "https://github.com/SymmetryLabs/cpp.react.git"
  USE_CACHING TRUE
  )

# set(REPO_SOURCE_DIR "/Users/Kyle/code/opensource/cpp.react")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Invoke CMake
SET(build_examples OFF CACHE BOOL "Build examples?")
add_subdirectory("${REPO_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/${__CPM_FULL_UNID}/build")

CPM_ExportAdditionalIncludeDir("${REPO_SOURCE_DIR}/include")
CPM_ExportAdditionalLibraryTarget("CppReact")
