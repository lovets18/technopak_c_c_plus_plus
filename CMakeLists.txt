cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

set(LIB_SOURCE_FILES server.c)
add_library(server STATIC ${LIB_SOURCE_FILES})

add_compile_options("-lgcov --coverage")




add_executable(main main.c)
target_link_libraries(main server)

target_link_libraries(main gcov)



enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(server_test server_test.cpp)
target_link_libraries(server_test ${GTEST_LIBRARIES} server)

