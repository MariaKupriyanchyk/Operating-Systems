cmake_minimum_required(VERSION 3.15)
project(cmake_os_lab1_project)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Добавляем подпроекты
add_subdirectory(cmake_os_lab1)
add_subdirectory(tests)
