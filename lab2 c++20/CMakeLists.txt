cmake_minimum_required(VERSION 3.15)
project(Os_lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(Os_lab2
    src/main.cpp
    src/array_utils.cpp
    src/min_max_thread.cpp
    src/average_thread.cpp
    include/array_utils.h
    include/min_max_thread.h
    include/average_thread.h
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(Tests
    tests/test_average_thread.cpp
    tests/test_min_max_thread.cpp
    src/array_utils.cpp
    src/min_max_thread.cpp
    src/average_thread.cpp
    include/array_utils.h
    include/min_max_thread.h
    include/average_thread.h
)
target_link_libraries(Tests PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)
