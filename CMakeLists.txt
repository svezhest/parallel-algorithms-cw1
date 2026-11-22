cmake_minimum_required(VERSION 3.14)
project(ParlayHelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    parlaylib
    GIT_REPOSITORY https://github.com/cmuparlay/parlaylib.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(parlaylib)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

set(GTEST_INCLUDE_DIR "${googletest_SOURCE_DIR}/googletest/include")
foreach(gtest_target gtest gtest_main)
    if(TARGET ${gtest_target})
        target_include_directories(${gtest_target} BEFORE PUBLIC
            "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIR}>")
        set_property(TARGET ${gtest_target} PROPERTY
            INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "")
    endif()
endforeach()

enable_testing()

add_library(quicksort_seq src/sec.cpp)
target_include_directories(quicksort_seq PUBLIC src)
target_link_libraries(quicksort_seq PUBLIC parlay)

add_executable(bench src/bench.cpp)
target_link_libraries(bench PRIVATE quicksort_seq)

add_executable(test_hello test/test.cpp)
target_link_libraries(test_hello PRIVATE quicksort_seq GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_hello)
