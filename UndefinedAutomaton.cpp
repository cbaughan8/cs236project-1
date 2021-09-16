#include "UndefinedAutomaton.h"
#include <cctype>

void UndefinedAutomaton::S0(const std::string& input) {
    if (input[index] == '#'){
        ++inputRead;
        ++index;
        S1(input);
    }
    else if (input[index] == '\''){
        ++inputRead;
        ++index;
        S4(input);
    }
    else if (isspace(input[index]) || input[index] == '\n' || input[index] == EOF) Serr();
    else{
        ++inputRead;
        ++index;
    }
}

void UndefinedAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        ++inputRead;
        ++index;
        S2(input);
    }
    else { Serr();}
}

void UndefinedAutomaton::S2(const std::string& input) {
    if (input[index] == '|') {
        ++inputRead;
        ++index;
        S3(input);
    }
    else if (input[index] == EOF);
    else if (index >= input.size());
    else {
        if (input[index] == '\n') ++newLines;
        ++inputRead;
        ++index;
        S2(input);
    }
}

void UndefinedAutomaton::S3(const std::string& input) {
    if (input[index] == '#') Serr();
    else if (input[index] == EOF);
    else if (index >= input.size());
    else {
        if (input[index] == '\n') ++newLines;
        ++inputRead;
        ++index;
        S2(input);
    }
}

void UndefinedAutomaton::S4(const std::string& input) {
    if (input[index] == '\'') {
        ++inputRead;
        ++index;
        S5(input);
    }
    else if (input[index] == EOF);
    else if (index >= input.size());
    else {
        if (input[index] == '\n') ++newLines;
        ++inputRead;
        ++index;
        S4(input);
    }
}

void UndefinedAutomaton::S5(const std::string& input) {
    if (input[index] == '\'') {
        ++inputRead;
        ++index;
        S4(input);
    }
    else { Serr();}
}

