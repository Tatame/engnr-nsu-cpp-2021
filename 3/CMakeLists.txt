cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

enable_testing()

include_directories(googletest/googletest/include)

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

target_link_libraries(linked_list_tests
        gtest
        gmock_main
        )

add_test(NAME googletest COMMAND linked_list_tests)