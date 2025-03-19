#include "lexer.h";
#include <iostream>

Lexer::Lexer(const std::string& src) : src(src), pos(0) {}

char Lexer::peek() {
    return pos < src.size() ? src[pos]: '\0';
}

char Lexer::get() {
    return pos < src.size() ? src[pos++] : '\0';
}

void Lexer::skipWhiteSpace() {
    while (isspace(peek())) get();
}

Token Lexer::getNextToken() {
    skipWhiteSpace();

    char current = peek();
    if(current == '\0') return { TokenType::END_OF_FILE, ""};

    // Identifiers or Keywords
    if (isalpha(current)) {
        std::string ident;
        while (isalnum(peek())) ident += get();

        if (ident == "int" || ident == "float" || ident == "if" || ident == "else" || ident == "while") {
            return {TokenType::KEYWORD, ident};
        }

        return {TokenType::IDENTIFIER, ident};
    }

    // Numbers
    if (isdigit(current)) {
        std::string number;
        while (isdigit(peek()) || peek() == '.') number += get();
        return {TokenType::NUMBER, number};
    }

    // Symbols
    std::string sym(1, get());
    return {TokenType::SYMBOL, sym};
}