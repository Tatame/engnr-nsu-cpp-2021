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
stack = ReadFromStream(data);
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
stack = ReadFromStream(data);
EXPECT_EQ(stack.get_result(), value);
}

TEST(CALC3, EXCECUTION_TEST_ONE) {
std::stringstream data("PUSH 5\n"
                       "PUSH 5\n"
                       "MINUS\n"
                       "POP\n"
                       "POP\n");
EXPECT_THROW(ReadFromStream(data), StackIsEmpty);
}

TEST(CALC4, EXCECUTION_TEST_TWO) {
std::stringstream data("# 5+5\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromStream(data), FewElementsException);
}

TEST(CALC5, EXCECUTION_TEST_THREE) {
std::stringstream data("PUSH 8\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "PUSH 5\n"
                       "PLUS\n"
                       "DROW"
                      );
EXPECT_THROW(ReadFromStream(data), WrongCommand);
}

TEST(CALC6, EXCECUTION_TEST_FOUR) {
std::stringstream data("# 5+5\n"
                       "PUSH 5\n"
                       "PUSH %\n"
                       "PLUS\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromStream(data), WrongArgument);
}

TEST(CALC7, EXCECUTION_TEST_4) {
std::stringstream data("# 2/(5-5)\n"
                       "PUSH 2\n"
                       "PUSH 5\n"
                       "PUSH 5\n"
                       "MINUS\n"
                       "DIV\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromStream(data), DivisionByZero);
}

TEST(CALC8, EXCECUTION_TEST_04) {
std::stringstream data("PUSH 9223372036854775806\n"
                       "PUSH 1000\n"
                       "PLUS\n"
                       "PRINT"
                      );
EXPECT_THROW(ReadFromStream(data), OverflowException);
}

TEST(CALC9, EXCECUTION_TEST_PYAT) {
    std::stringstream data("PUSH -9223372036854775808\n"
                           "PUSH -1\n"
                           "DIV\n"
                           "PRINT"
    );
    EXPECT_THROW(ReadFromStream(data), OverflowException);
}

TEST(CALC10, EXCECUTION_TEST_SIX) {
    std::stringstream data("PUSH 853373436854\n"
                           "PUSH 20898131\n"
                           "MUL\n"
                           "PRINT\n"
    );
    EXPECT_THROW(ReadFromStream(data), OverflowException);
}

TEST(CALC11, EXCECUTION_TEST_SEVEN) {
    std::stringstream data("PUSH -9223372036854775808\n"
                           "ABS\n"
                           "PRINT\n"
    );
    EXPECT_THROW(ReadFromStream(data), OverflowException);
}

TEST(CALC11, EXCECUTION_TEST_8) {
    std::stringstream data("PUSH 100000000000000000000000\n"
                           "PRINT\n"
    );
    EXPECT_THROW(ReadFromStream(data), OverflowException);
}
