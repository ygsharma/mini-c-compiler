#include "lexer.h"
#include <cctype>
#include <iostream>

// Constructor
Lexer::Lexer(SourceBuffer& buffer): src(buffer) {}


void Lexer::skipWhiteSpace() {
    while (!src.eof() && std::isspace(src.peekChar())) {
        src.getChar();
    }
}

void Lexer::reportError(const std::string& message, int line, int col) {
    std::cerr << src.getFilename() << ":" << line << ":" << col << ": error: " << message << "\n";
}

// return the next token in the file
Token Lexer::getNextToken() {
    skipWhiteSpace();

    int tokenLine = src.getLine();
    int tokenCol = src.getColumn();

    if (src.eof()) {
        return {TokenType::END_OF_FILE, "", tokenLine, tokenCol};
    }

    char ch = src.peekChar();

    // Identifiers or Keywords
    if (std::isalpha(ch) || ch == '_') {
        std::string ident;
        while (std::isalnum(src.peekChar())) {
            ident += src.getChar();
        }

        if (ident == "int" || ident == "float" || ident == "if" || ident == "else" || ident == "while") {
            return {TokenType::KEYWORD, ident, tokenLine, tokenCol};
        }

        return {TokenType::IDENTIFIER, ident, tokenLine, tokenCol};
    }

    // Numbers
    if (isdigit(ch)) {
        std::string number;
        while (isdigit(src.peekChar()) || src.peekChar() == '.') {
            number += src.getChar();
        }
        return {TokenType::NUMBER, number, tokenLine, tokenCol};
    }

    // Symbols
    std::string sym(1, src.getChar());
    if (sym == ";" || sym == "=" || sym == "+" || sym == "-" || sym == "*" || sym == "/" || sym == "(" || sym == ")" || sym == "{" || sym == "}") {
        return {TokenType::SYMBOL, sym, tokenLine, tokenCol};
    }

    reportError("unexpected character '" + sym + "'", tokenLine, tokenCol);
    return {TokenType::SYMBOL, sym, tokenLine, tokenCol};
}