#############################################################################
# PokePets Unit Tests
#############################################################################
project(PokePets_utest)

#############################################################################
# Including Google C++ Testing Framework
# Defaults ${gtest_EXTERNAL_SOURCE_DIR} to ${PROJECT_SOURCE_DIR}/gtest
# if not found, user must specify the location of gtest
#############################################################################
SET(gtest_EXTERNAL_SOURCE_DIR gtest CACHE PATH "gtest")
add_subdirectory(${gtest_EXTERNAL_SOURCE_DIR} gtest)

include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})


#############################################################################
# From
# stackoverflow.com/questions/7262370/
#     unit-test-output-project-structure-advice-cmake-google-test-framework
#############################################################################
macro(run_test test_target)
  add_custom_target(${test_target}_runtest
      COMMAND ${test_target} #cmake 2.6 required
      DEPENDS ${test_target}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
  add_dependencies(test ${test_target}_runtest)
endmacro()

#################################################   ############################
# Tests an object library with Google C++ Testing Framework
#
# this_test(<name> <lib>)
#
# <name> is the object library under test
#  - <name>Test.cc is the unit test code for the object library
# <lib> is gtest or gtest_main (if implementation has main)
# <ARGN> are additional dependencies that are already added as object library
#############################################################################
function(test_this NAME LIB)
    # Helper function from Google C++ Testing Framework
    set(TEST_DEP ../src/${NAME})

    foreach(obj ${ARGN})
       set(TEST_DEP ${TEST_DEP} ../src/${obj})
    endforeach(obj)

    cxx_executable(
        ${NAME}Test . ${LIB} ${TEST_DEP})
    # link all dependencies
    # target_link_libraries(${NAME}Test ${NAME} ${ARGN})
    run_test(${NAME}Test)
endfunction()

#############################################################################
# My Unit Tests
#############################################################################
test_this(PokemonSpecies gtest_main CSVReader PokemonBuilder Type)
test_this(CSVReader gtest)