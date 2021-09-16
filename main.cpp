#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    std::string input;

    std::ifstream in(argv[1]);

    while(in.peek() != EOF){
        char inputChar = in.get();
        input = input + inputChar;
    }

    lexer->Run(input);
    std::cout << input;
    lexer->TotalTokens();

    delete lexer;

    return 0;
}