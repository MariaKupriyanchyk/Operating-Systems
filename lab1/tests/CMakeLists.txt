cmake_minimum_required(VERSION 3.15)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

#include_directories(${CMAKE_SOURCE_DIR}/cmake_os_lab1)

message(STATUS ">>> Tests.cpp full path: ${CMAKE_SOURCE_DIR}/tests/Tests.cpp")

add_executable(tests
    ${CMAKE_SOURCE_DIR}/tests/Tests.cpp
    ${CMAKE_SOURCE_DIR}/cmake_os_lab1/employee.cpp
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/cmake_os_lab1)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_test(NAME MyTests COMMAND tests)