#include <iostream>
#include "source_buffer.h"
#include "lexer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.c>\n";
        return 1;
    }

    SourceBuffer buffer(argv[1]);
    Lexer lexer(buffer);

    Token token;
    while (token.type != TokenType::END_OF_FILE) {
        token = lexer.getNextToken();

        if (token.type != TokenType::ERROR && token.type != TokenType::END_OF_FILE) {
            std::cout << "Token: " << token.value << " (Line: )" << token.line << ", Column: " << token.column << ")\n";
        }
    }
    return 0;
}
