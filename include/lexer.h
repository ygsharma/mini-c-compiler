#ifndef LEXER_H
#define LEXER_H


#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, SYMBOL, END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& src);
    Token getNextToken();

private:
    std::string src;
    size_t pos;
    char peek();
    char get();
    void skipWhiteSpace();
};

#endif;