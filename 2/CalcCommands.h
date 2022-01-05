#ifndef INC_2_CALCCOMMANDS_H
#define INC_2_CALCCOMMANDS_H

#include "CalcException.h"

class Action {
public:
    std::stack<SafeInt<int64_t, IntOverflowException>> stack;
    std::map<std::string, SafeInt<int64_t, IntOverflowException>> vars;
};

class Commands {
public:
    explicit Commands(std::string &args) {arguments = args;}

    virtual void command_type(Action &action) = 0;

    virtual ~Commands() = default;

protected:
    std::string arguments;
};

class Comment : public Commands{
public:
    explicit Comment(std::string &args) : Commands(args) {};
    void command_type(Action &action) override {};
};

class Pop : public Commands{
public:
    explicit Pop(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Push : public Commands{
public:
    explicit Push(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Peek : public Commands{
public:
    explicit Peek(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Abs : public Commands{
public:
    explicit Abs(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Plus : public Commands{
public:
    explicit Plus(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Minus : public Commands{
public:
    explicit Minus(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Mul : public Commands{
public:
    explicit Mul(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Div : public Commands{
public:
    explicit Div(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Print : public Commands{
public:
    explicit Print(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class Read : public Commands{
public:
    explicit Read(std::string &args) : Commands(args) {};
    void command_type(Action &action) override;
};

class My_Stack {
private:
    Action action;
public:
    void new_command(std::unique_ptr<Commands> command);

    static Commands* read_command(std::string &str);
};

My_Stack ReadFromFile(std::istream &file);

My_Stack ReadFromCin();

#endif //INC_2_CALCCOMMANDS_H