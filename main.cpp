#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();
    std::string input;


    std::ifstream in(argv[1]);

    while(in.peek() != EOF){
        char inputChar = in.get();
        input = input + inputChar;
    }

    lexer->Run(input);

    //maybe get rid of input later
    //std::cout << input;
    //lexer->TotalTokens();
    try {
        //std::cout << parser->TokensToString();
        parser->Run(lexer->GetTokens());
    }
    catch(std::string e){
        std::cout << e << std::endl;
    }





    delete lexer;
    delete parser;

    return 0;
}