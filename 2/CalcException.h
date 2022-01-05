#ifndef INC_2_CALCEXCEPTION_H
#define INC_2_CALCEXCEPTION_H

#include <string>
#include <stack>
#include <map>
#include <sstream>
#include <cmath>
#include <iostream>
#include <utility>
#include "SafeInt/SafeInt.hpp"
#include <memory>

class CalcException : public std::runtime_error {
private:
    const std::string name;
public:
    explicit CalcException(const std::string &error) : std::runtime_error(error), name(error) {};
    const char *what() const noexcept override {
            return name.c_str();
    }
};

class StackIsEmpty : public CalcException {
public:
    StackIsEmpty() : CalcException("Stack is Empty") {}
};

class DivisionByZero : public CalcException {
public:
    DivisionByZero() : CalcException("There is a division by zero") {}
};

class WrongCommand : public CalcException {
public:
    WrongCommand() : CalcException("The command is not defined") {}
};

class WrongArgument : public CalcException {
public:
    WrongArgument() : CalcException("Not enough arguments or they are wrong") {}
};

class FewElementsException : public CalcException {
public:
    FewElementsException() : CalcException("There are not enough elements to perform the operation") {}
};

class OverflowException : public CalcException {
public:
    OverflowException() : CalcException("OverflowException") {}
};

class IntOverflowException : public SafeIntException{
public:
    static void SafeIntOnOverflow(){
        throw OverflowException();
    }
};


#endif //INC_2_CALCEXCEPTION_H
