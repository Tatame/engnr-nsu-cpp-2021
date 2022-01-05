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
    std::string er_name =  "Stack is Empty";
public:
    explicit StackIsEmpty(const std::string &error) : CalcException(error) {};
    StackIsEmpty() : CalcException(er_name) {}
};

class DivisionByZero : public CalcException {
    std::string er_name =  "There is a division by zero";
public:
    explicit DivisionByZero(const std::string &error) : CalcException(error) {};
    DivisionByZero() : CalcException(er_name) {}
};

class WrongCommand : public CalcException {
    std::string er_name =  "The command is not defined";
public:
    explicit WrongCommand(const std::string &error) : CalcException(error) {};
    WrongCommand() : CalcException(er_name) {}
};

class WrongArgument : public CalcException {
    std::string er_name =  "Not enough arguments or they are wrong";
public:
    explicit WrongArgument(const std::string &error) : CalcException(error) {};
    WrongArgument() : CalcException(er_name) {}
};

class OverflowException : public CalcException {
    std::string er_name =  "OverflowException";
public:
    explicit OverflowException(const std::string &error) : CalcException(error) {};
    OverflowException() : CalcException(er_name) {}
};

class IntOverflowException : public SafeIntException{
public:
    static void SafeIntOnOverflow(){
        throw OverflowException();
    }
};

//WrongArgument
//

//
//FewElementError
//
//OverflowException
//
//class MyException : public SafeIntException{
//public:
//    static void SIOverflow();
//};


#endif //INC_2_CALCEXCEPTION_H
