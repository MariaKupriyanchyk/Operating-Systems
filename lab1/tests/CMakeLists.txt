cmake_minimum_required(VERSION 3.15)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL" CACHE STRING "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(tests
    ${CMAKE_SOURCE_DIR}/tests/Tests.cpp
    ${CMAKE_SOURCE_DIR}/cmake_os_lab1/employee.cpp
)

set_target_properties(tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/cmake_os_lab1)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_test(NAME MyTests COMMAND tests)
