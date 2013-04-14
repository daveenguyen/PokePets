#############################################################################
# PokePets
#############################################################################
cmake_minimum_required(VERSION 2.8)

project(PokePets)

set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 0)
set(CMAKE_PATCH_VERSION 0)

option(pp_tests "Build all unit tests for PokePets." OFF)

#############################################################################
# Sets output directory for executables
# set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR})
SET (CTEST_SOURCE_DIRECTORY ${CMAKE_BINARY_DIR})
SET (CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR})


#############################################################################
add_custom_target(main
  COMMAND PokePets #cmake 2.6 required
  DEPENDS PokePets
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
add_subdirectory(src)

# if testing
if (pp_tests)
    add_custom_target(test)
    add_subdirectory(test)
endif(pp_tests)