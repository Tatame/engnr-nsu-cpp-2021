set(CMAKE_CXX_STANDARD 17)

add_executable(calculator_tests tests.cpp ../main.cpp ../CalcException.h ../CalcCommands.cpp ../CalcCommands.h)

target_include_directories(calculator_tests
   PRIVATE "../"
        )

target_link_libraries(calculator_tests
        gtest
        gmock_main
        )

enable_testing()
add_test(NAME google_test COMMAND calculator_tests)
