#include "CalcCommands.h"
#include "CalcException.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../SafeInt/SafeInt.hpp"
#include <stdexcept>

int main(int argc, char *argv[]) {
    try {
        std::string path, phrase;
        phrase = "You should use : ./calculator <filename> or ./calculator\n"
                 "Commands: #, POP, PUSH <number>, PEEK <varname>, PUSH <varname>, ABS, PLUS, MINUS, MUL, DIV, PRINT, READ.";
        if (argc == 2){
            path = argv[1];
            std::ifstream file;
            file.open(path);
            if (!file.is_open()){
                std::cerr << "Error: File is not found" << std::endl << phrase << std::endl;
                return 1;
            }
            ReadFromFile(file);
        } else if (argc == 1){
            ReadFromCin();
        } else{
            std::cerr << "Error: unknown command" << std::endl << phrase << std::endl;
        }
    }
    catch (const std::runtime_error &error){
        std::cerr << error.what() << std::endl;
        return 1;
    }
    // One more exception...
    return 0;
}

