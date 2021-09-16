#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#'){
        ++inputRead;
        ++index;
        S1(input);
    }
    else{
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|'){
        ++inputRead;
        ++index;
        S3(input);
    }
    else if(input[index] == '\n'){}
    else if(input[index] == EOF){}
    else if (index >= input.size()){}
    else{
        ++inputRead;
        ++index;
        S2(input);
    }

}

void CommentAutomaton::S2(const std::string& input) {
    if (input[index] == '\n'){
    }
    else if (input[index] == EOF){}
    else if (index >= input.size()){}
    else {
        ++inputRead;
        ++index;
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string& input) {
    if (input[index] == '|'){
        ++inputRead;
        ++index;
        S4(input);
    }
    else if (input[index] == EOF){ Serr(); }
    else if (index >= input.size()){ Serr();}
    else{
        if(input[index] == '\n') ++newLines;
        ++inputRead;
        ++index;
        S3(input);
    }
}

void CommentAutomaton::S4(const std::string& input) {
    if (input[index] == '#'){
        ++inputRead;
        ++index;
    }
    else if (input[index] == EOF) { Serr();}
    else {
        if(input[index] == '\n') ++newLines;
        ++inputRead;
        ++index;
        S3(input);
    }
}

