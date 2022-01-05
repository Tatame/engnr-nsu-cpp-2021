cmake_minimum_required(VERSION 3.20)
project(2)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp CalcException.h CalcCommands.cpp CalcCommands.h)
