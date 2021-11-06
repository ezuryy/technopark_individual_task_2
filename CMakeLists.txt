cmake_minimum_required(VERSION 3.20)
project(test_processes)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror -fprofile-arcs -ftest-coverage -fpic")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage -fpic")

# libraries
add_library(common_files STATIC
        common_functions/common_functions.c)
target_include_directories(common_files PUBLIC
        ${PROJECT_SOURCE_DIR}/common_functions)

# lib_static
add_library(_static SHARED consistent_implementation/consistent.c)
target_include_directories(_static PUBLIC ${PROJECT_SOURCE_DIR}/consistent_implementation)
target_link_libraries(_static common_files)

# lib_dynamic
add_library(_dynamic SHARED parallel_implementation/parallel.c)
target_include_directories(_dynamic PUBLIC ${PROJECT_SOURCE_DIR}/parallel_implementation)
target_link_libraries(_dynamic common_files)

# main
add_executable(main main.c)
target_include_directories(main PUBLIC
        ${PROJECT_SOURCE_DIR}/common_functions)
target_link_libraries(main _dynamic _static common_files)

# gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# test common files
add_executable(test_common_files
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test_common_files.cpp)
target_include_directories(test_common_files PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/common_functions)
target_link_libraries(test_common_files gtest_main common_files)
include(GoogleTest)
gtest_discover_tests(test_common_files)

# test consistent
add_executable(test_consistent
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test_consistent.cpp)
target_include_directories(test_consistent PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/consistent_implementation)
target_link_libraries(test_consistent gtest_main _static)

# test parallel
add_executable(test_parallel
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test_parallel.cpp)
target_include_directories(test_parallel PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/parallel_implementation)
target_link_libraries(test_parallel gtest_main _dynamic)

include(GoogleTest)
gtest_discover_tests(test_common_files test_consistent test_parallel)
