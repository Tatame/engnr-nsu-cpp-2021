cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(List main.cpp LinkedList.h)

enable_testing()

include_directories(googletest/googletest/include)

add_executable(List_tests tests.cpp )

target_include_directories(List_tests PRIVATE "../googletest/googletest/include")

target_link_libraries(List_tests gtest gmock_main)

add_test(NAME googletests COMMAND List_tests)
