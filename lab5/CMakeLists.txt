cmake_minimum_required(VERSION 3.16)
project(Os_lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Main
    src/file_storage.cpp
    src/pipe_protocol.cpp
)

add_executable(server
    src/server.cpp
)
target_link_libraries(server PRIVATE Main)

add_executable(client
    src/client.cpp
)
target_link_libraries(client PRIVATE Main)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests
    tests/tests.cpp
)
target_link_libraries(Tests PRIVATE Main gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)