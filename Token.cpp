#include "Token.h"
#include <sstream>

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::toString() {
    std::stringstream ss;
    ss << "(";
    switch(type){
        case TokenType::COLON: ss << "COLON"; break;
        case TokenType::COLON_DASH: ss << "COLON_DASH"; break;
        case TokenType::COMMA: ss << "COMMA"; break;
        case TokenType::PERIOD: ss << "PERIOD"; break;
        case TokenType::Q_MARK: ss << "Q_MARK"; break;
        case TokenType::LEFT_PAREN: ss << "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: ss << "RIGHT_PAREN"; break;
        case TokenType::MULTIPLY: ss << "MULTIPLY"; break;
        case TokenType::ADD: ss << "ADD"; break;
        case TokenType::SCHEMES: ss << "SCHEMES"; break;
        case TokenType::FACTS: ss << "FACTS"; break;
        case TokenType::RULES: ss << "RULES"; break;
        case TokenType::QUERIES: ss << "QUERIES"; break;
        case TokenType::ID: ss << "ID"; break;
        case TokenType::STRING: ss << "STRING"; break;
        case TokenType::COMMENT: ss << "COMMENT"; break;
        case TokenType::EOF_ENUM: ss << "EOF"; break;
        case TokenType::UNDEFINED: ss << "UNDEFINED"; break;
        default: break;
    }
    ss << "," << "\"" << description << "\"," << line << ")\n";

    return ss.str();
}
