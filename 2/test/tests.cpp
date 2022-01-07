#include "gtest/gtest.h"
#include <fstream>
#include "../CalcException.h"
#include "../CalcCommands.h"


TEST(CALC1, FIRST_TEST) {
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
EXPECT_EQ(stack.get_result(), value);
}

TEST(CALC2, SECOND_TEST) {
std::stringstream data("# |(1 + 2 + 3 + 4 + 5) / 5 * (-3)|\n"
                       "PUSH 1\n"
                       "PUSH 2\n"
                       "PLUS\n"
                       "PUSH 3\n"
                       "PLUS \n"
                       "PUSH 4\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "DIV\n"
                       "PUSH -3\n"
                       "MUL\n"
                       "ABS\n"
                       "PRINT"
                       );
int64_t value = 9;
My_Stack stack;
stack = ReadFromFile(data);
EXPECT_EQ(stack.get_result(), value);
}

TEST(CALC3, EXCECUTION_TEST_ONE) {
std::stringstream data("PUSH 5\n"
                       "PUSH 5\n"
                       "MINUS\n"
                       "POP\n"
                       "POP\n");
EXPECT_THROW(ReadFromFile(data), StackIsEmpty);
}

TEST(CALC4, EXCECUTION_TEST_TWO) {
std::stringstream data("#5+5\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromFile(data), FewElementsException);
}

TEST(CALC5, EXCECUTION_TEST_THREE) {
std::stringstream data("PUSH 8\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "DROW"
                      );
EXPECT_THROW(ReadFromFile(data), WrongCommand);
}

TEST(CALC6, EXCECUTION_TEST_FOUR) {
std::stringstream data("#5+5\n"
                       "PUSH 5\n"
                       "PUSH %\n"
                       "PLUS\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromFile(data), WrongArgument);
}

TEST(CALC7, EXCECUTION_TEST_FOUR) {
std::stringstream data("#2/(5-5)\n"
                       "PUSH 5\n"
                       "PUSH 5\n"
                       "MINUS\n"
                       "PUSH 2\n"
                       "DIV"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromFile(data), DivisionByZero);
}

TEST(CALC8, EXCECUTION_TEST_FOUR) {
std::stringstream data("PUSH 9 223 372 036 854 775 806\n"
                       "PUSH 1000\n"
                       "PLUS"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromFile(data), OverflowException);
} 
