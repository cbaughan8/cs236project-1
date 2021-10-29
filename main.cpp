#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
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

    try {
        //std::cout << parser->TokensToString();
        parser->Run(lexer->GetTokens());
        Interpreter* interpreter = new Interpreter(parser->GetDatalogProgram());
        interpreter->run();
    }
    catch(std::string e){
        std::cout << e;
    }





    delete lexer;
    delete parser;
    //delete interpreter;

    return 0;
}