cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#-----------------------------------------------------------------------
# CPM configuration
#-----------------------------------------------------------------------
set(CPM_MODULE_NAME cxx_prettyprint)
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

#------------------------------------------------------------------------------
# libnoise
#------------------------------------------------------------------------------

if (APPLE)
  set(CMAKE_MACOSX_RPATH TRUE)
endif()

# Download source code
set(REPO_SOURCE_DIR "${CMAKE_BINARY_DIR}/${__CPM_FULL_UNID}/repo")
CPM_EnsureRepoIsCurrent(
  TARGET_DIR ${REPO_SOURCE_DIR}
  GIT_REPOSITORY "https://github.com/louisdx/cxx-prettyprint.git"
  GIT_TAG "334db032471126dd5c47e5ed27a5d0af5d46d068"
  USE_CACHING TRUE
  )

CPM_ExportAdditionalIncludeDir("${REPO_SOURCE_DIR}")
