cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(List main.cpp LinkedList.h)

if (WIN32)
    
else()
    target_compile_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
    target_link_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
endif()

enable_testing()

add_subdirectory(googletest)

add_executable(List_tests tests.cpp )

target_link_libraries(List_tests gtest gmock_main)

add_test(NAME googletest COMMAND List_tests)
