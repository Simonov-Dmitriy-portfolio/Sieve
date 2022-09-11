cmake_minimum_required(VERSION 3.8)

project(sieve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    src/sieve.cpp
   )

add_library(sieve ${sources})

target_include_directories(sieve PUBLIC include/sieve)

set(test_sources
    testsrc/sieve_test.cpp
   )

add_executable(sieve_test ${test_sources})

target_include_directories(sieve_test PUBLIC include)

target_link_libraries(sieve_test sieve)
