#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include "Token.h"
#include "DatalogProgram.h"

#include <vector>

class Parser
{
private:
    std::vector<Token*> tokens;
public:
    Parser();
    ~Parser();

    DatalogProgram* Run(std::vector<Token*> tokens);
    void ClearComments();
    std::string TokensToString();


};

#endif //PROJECT_1_PARSER_H
