include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES employee.cpp employee.h)

add_executable(Main Main.cpp ${SOURCES})
add_executable(Creator Creator.cpp ${SOURCES})

add_executable(Reporter Reporter.cpp ${SOURCES})
