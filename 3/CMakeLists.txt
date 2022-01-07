cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/googletest)

enable_testing()

include_directories(libs/googletest/googletest/include)

add_executable(lab3 main.cpp)

add_executable(linked_list_tests tests.cpp)

if (WIN32)
    #do something
else()
    target_compile_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
    target_link_options(linked_list_tests PUBLIC
            -fno-omit-frame-pointer -fsanitize=address)
endif()


add_library(linked_list_lib STATIC linked_list.cpp linked_list.h)

target_link_libraries(lab3 linked_list_lib)

target_link_libraries(linked_list_tests
        linked_list_lib
        gtest
        gmock_main
        )

add_test(NAME googletest COMMAND linked_list_tests)