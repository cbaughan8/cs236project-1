#include "Parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

DatalogProgram* Parser::Run(std::vector<Token*> tokens){
    this->tokens = tokens;
    ClearComments();
    DatalogProgram* datalogProgram = new DatalogProgram(this->tokens);
    datalogProgram->Init(datalogProgram);


    // maybe make a deep copy
    return datalogProgram;
}

void Parser::ClearComments() {
    for(unsigned int i = 0; i < tokens.size(); ++i){
        if (tokens.at(i)->GetType() == TokenType::COMMENT){
            tokens.erase(tokens.begin() + i);
            --i;
        }

    }
}

std::string Parser::TokensToString() {
    std::string tokenString;
    for (unsigned int i = 0; i < tokens.size(); ++i){
        tokenString = tokenString += tokens.at(i)->toString();
    }
    return tokenString;
}
