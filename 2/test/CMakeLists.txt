set(CMAKE_CXX_STANDARD 17)

add_executable(calculator_tests tests.cpp )

target_include_directories(calculator_tests PRIVATE "../googletest/googletest/include")

target_link_libraries(calculator_tests gtest gmock_main calc_l)

enable_testing()
add_test(NAME googletest COMMAND calculator_tests)
