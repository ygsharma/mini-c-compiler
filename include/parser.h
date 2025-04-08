#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

class Parser {
public:
    explicit Parser(Lexer& lexer);
    std::shared_ptr<StatementListNode> parseProgram();

private:
    Lexer& lexer;
    Token currentToken;

    void advance();
    void expect(TokenType type, const std::string& value = "");

    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseAssignment();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
};

#endif
