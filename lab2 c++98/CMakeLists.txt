cmake_minimum_required(VERSION 3.10)
project(Os_lab2_c98 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Main)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(threads_lib
    src/array_utils.cpp
    src/average_thread.cpp
    src/min_max_thread.cpp
)

target_link_libraries(threads_lib PRIVATE ws2_32)

add_executable(Main src/main.cpp)
target_link_libraries(Main PRIVATE threads_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(UnitTests ${TEST_SOURCES})
target_include_directories(UnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(UnitTests PRIVATE threads_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)
