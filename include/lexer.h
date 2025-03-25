#ifndef LEXER_H
#define LEXER_H

#include "source_buffer.h"
#include "token.h"

class Lexer {
    
    public:
        Lexer(SourceBuffer& buffer);
        Token getNextToken();

    private:
        SourceBuffer& src;

        void skipWhiteSpace();
        void reportError(const std::string& message, int line, int col);

};

#endif