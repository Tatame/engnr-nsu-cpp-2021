#include "CalcException.h"
#include "CalcCommands.h"
#include <algorithm>
#include <charconv>


void Pop::command_type(Action &action) {
    if (!action.stack.empty()){
        action.stack.pop();
    } else{
        throw StackIsEmpty();
    }
}

void Push::command_type(Action &action) {
    if (arguments.empty()){
        throw WrongArgument();
    }
    if ((arguments[0] == '-' || std::isdigit(arguments[0])) &&
        std::all_of(arguments.begin()+1, arguments.end(), [](char ch){return std::isdigit(ch);})){
        int64_t result{};
        auto er =  std::from_chars(arguments.data(), arguments.data() + arguments.size(), result);
        if (er.ec == std::errc::invalid_argument || er.ec == std::errc::result_out_of_range){
            throw WrongArgument();
        }
        action.stack.push(result);
    } else{
        auto pos = action.vars.find(arguments);
        if (pos == action.vars.end()){
            throw WrongArgument();
        } else {
            action.stack.push(pos->second);
        }
    }
}

void Peek::command_type(Action &action) {
    if (action.stack.empty()){
        throw StackIsEmpty();
    } else {
        action.vars[arguments] = action.stack.top();
    }
}

void Abs::command_type(Action &action) {
    if (action.stack.empty()){
        throw StackIsEmpty();
    } else {
        SafeInt<int64_t, IntOverflowException> value = action.stack.top();
        action.stack.pop();
        if (value < 0){
            action.stack.push(-value);
        } else {
            action.stack.push(value);
        }
    }
}

void Plus::command_type(Action &action) {
    if (action.stack.size() < 2){
        throw FewElementsException();
    } else {
        SafeInt<int64_t, IntOverflowException> value_one = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_two = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_sum = value_one + value_two;
        action.stack.push(value_sum);
    }
}

void Minus::command_type(Action &action) {
    if (action.stack.size() < 2){
        throw FewElementsException();
    } else {
        SafeInt<int64_t, IntOverflowException> value_one = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_two = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_min = value_two - value_one;
        action.stack.push(value_min);
    }
}

void Mul::command_type(Action &action) {
    if (action.stack.size() < 2){
        throw FewElementsException();
    } else {
        SafeInt<int64_t, IntOverflowException> value_one = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_two = action.stack.top();
        action.stack.pop();
        SafeInt<int64_t, IntOverflowException> value_mul = value_two * value_one;
        action.stack.push(value_mul);
    }
}

void Div::command_type(Action &action) {
    if (action.stack.size() < 2){
        throw FewElementsException();
    } else {
        int64_t value_one = action.stack.top();
        action.stack.pop();
        if (value_one == 0){
            throw DivisionByZero();
        } else {
            int64_t value_two = action.stack.top();
            action.stack.pop();
            int64_t value_div;
            SafeDivide(value_two, value_one, value_div);
            action.stack.push(value_div);
        }
    }
}

void Print::command_type(Action &action) {
    if (action.stack.empty()){
        throw StackIsEmpty();
    } else {
        std::int64_t value = action.stack.top();
        std::cout << value << std::endl;
    }
}

void Read::command_type(Action &action) {
    std::string value;
    std::cin >> value;
    if ((value[0] == '-' || std::isdigit(value[0])) &&
        std::all_of(value.begin(), value.end(), [](char ch){return std::isdigit(ch);})){
        int64_t value_push;
        std::from_chars(value.data(), value.data() + value.size(), value_push);
        action.stack.push(value_push);
    } else {
        throw WrongArgument();
    }
}

void My_Stack::new_command(std::unique_ptr<Commands> command) {
    command->command_type(action);
}

Commands* My_Stack::read_command(std::string &str) {
    std::string command;
    std::string s = " ";
    std::stringstream stream;
    stream << str;
    stream >> command;
    Commands *type;
    if (str.empty()){
        return nullptr;
    } else if (command == "#"){
        type = new Comment(s);
    } else if (command == "POP"){
        type = new Pop(s);
    } else if (command == "PUSH"){
        stream >> command;
        type = new Push(command);
    } else if (command == "PEEK"){
        stream >> command;
        type = new Peek(command);
    } else if (command == "ABS"){
        type = new Abs(s);
    } else if (command == "PLUS"){
        type = new Plus(s);
    } else if (command == "MINUS"){
        type = new Minus(s);
    } else if (command == "MUL"){
        type = new Mul(s);
    } else if (command == "DIV"){
        type = new Div(s);
    } else if (command == "PRINT"){
        type = new Print(s);
    } else if (command == "READ"){
        type = new Read(s);
    } else {
        throw WrongCommand();
    }
    return type;
}

My_Stack ReadFromFile(std::istream &file){
    My_Stack calc;
    std::string command;
    while (!file.eof()){
        std::getline(file, command);
        std::unique_ptr<Commands> type(calc.read_command(command));
        if (type == nullptr) continue;
        else calc.new_command(std::move(type));

    }
    return calc;
}

My_Stack ReadFromCin(){
    My_Stack calc;
    std::string command;
    while (!std::cin.eof()){
        std::getline(std::cin, command);
        std::unique_ptr<Commands> type(calc.read_command(command));
        if (type == nullptr) continue;
        else calc.new_command(std::move(type));
    }
    return calc;
}

