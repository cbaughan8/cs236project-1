#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"

#include <iostream>



Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    /*for (unsigned int i = 0; i < automata.size(); ++i){
        delete automata.at(i);
    }*/
    for (unsigned int i = 0; i < tokens.size(); ++i){
        delete tokens.at(i);
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new EOFAutomaton());

}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0){
        int newline = 0;
        if(input.at(0) == '\n') newline = 1;
        lineNumber += newline;
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        for (unsigned int i = 0; i < automata.size(); ++i) {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        std::string newInput = input.substr(0, maxRead);
        if (maxRead > 0){
            Token* newToken = maxAutomaton->CreateToken(newInput, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            //Token* newToken = automata.at(16)->CreateToken(input, lineNumber);
            //tokens.push_back(newToken);
        }
        // update input here
        if (maxRead > 1){
            input = input.substr(maxRead , input.size() - maxRead);
        }
        else {
            input = input.substr(1, input.size() - 1);
        }
    }
    //EOF token
    //++lineNumber;
    Token* newToken = automata.at(17)->CreateToken("", lineNumber);
    tokens.push_back(newToken);

    for (unsigned int i = 0; i < tokens.size(); ++i){
        input = input += tokens.at(i)->toString();
    }

    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
    // delete memory for maxAutomata and newToken

}
void Lexer::TotalTokens() {
    std::cout << "Total Tokens = " << tokens.size() << std::endl;
}