#include "../../googletest/googletest/include/gtest/gtest.h"
#include <fstream>
#include "../CalcException.h"
#include "../CalcCommands.h"


TEST(CALC_ONE, FIRST_TEST) {
std::stringstream data("# myWish = 1000 + 1\n"
                       "PUSH 1000\n"
                       "PUSH 1\n"
                       "PLUS\n"
                       "PEEK myWish\n"
                       "POP\n"
                       "# PRINT (10000 - myWish) / 2\n"
                       "PUSH 10000\n"
                       "PUSH myWish\n"
                       "MINUS\n"
                       "PUSH 2\n"
                       "DIV\n"
                       "PRINT");
int64_t value = 4499;
My_Stack stack;
stack = ReadFromFile(data);
EXPECT_EQ(stack.action.stack.top(), value);
}

TEST(CALCULATOR1, ERROR_TEST) {
std::stringstream data("PUSH 5\n"
                       "PUSH 5\n"
                       "MINUS\n"
                       "POP\n"
                       "POP\n");
EXPECT_THROW(ReadFromStream(data), StackIsEmpty);
}

