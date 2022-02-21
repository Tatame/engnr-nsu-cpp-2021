cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(List main.cpp LinkedList.h)

enable_testing()

add_subdirectory(googletest)

add_executable(List_tests tests.cpp )

if (WIN32)
    #do
else()
    target_compile_options(List_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
    target_link_options(List_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
endif()


target_link_libraries(List_tests gtest gmock_main)

add_test(NAME googletest COMMAND List_tests)
