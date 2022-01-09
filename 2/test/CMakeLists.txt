set(CMAKE_CXX_STANDARD 17)

add_executable(calculator_tests tests.cpp )

target_include_directories(calculator_tests PRIVATE "../googletest/googletest/include")

target_link_libraries(calculator_tests gtest gmock_main calc_l)

add_test(NAME googletests COMMAND calculator_tests)
