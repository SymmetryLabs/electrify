cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_subdirectory (engine)
add_subdirectory (testapp)

enable_testing()
add_subdirectory(engine/test)
