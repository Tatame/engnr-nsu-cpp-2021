cmake_minimum_required(VERSION 3.20)
project(2)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp )

add_library(calc_l STATIC CalcException.h CalcCommands.cpp CalcCommands.h)



add_subdirectory(test)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(SafeInt)

include_directories(googletest/googletest/include)
include_directories(SafeInt/Test)

target_link_libraries(calculator calc_l)
