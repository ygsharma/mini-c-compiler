#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    KEYWORD, 
    IDENTIFIER, 
    NUMBER, 
    SYMBOL, 
    OPERATOR,
    END_OF_FILE, 
    ERROR
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

#endif