#include "parser.h"
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
    advance();
}

void Parser::advance() {
    currentToken = lexer.getNextToken();
}

void Parser::expect(TokenType type, const std::string& value) {
    if (currentToken.type != type || (!value.empty() && currentToken.value != value)) {
        std::cerr << "Syntax Error at Line " << currentToken.line << ", Column " << currentToken.column
                  << ": expected '" << value << "', got '" << currentToken.value << "'\n";
        exit(1);
    }
    advance();
}

std::shared_ptr<StatementListNode> Parser::parseProgram() {
    auto block = std::make_shared<StatementListNode>();
    while (currentToken.type != TokenType::END_OF_FILE) {
        auto stmt = parseStatement();
        if (stmt) {
            block->statements.push_back(stmt);
        }
    }
    return block;
}


// std::shared_ptr<StatementListNode> Parser::parseProgram() {
//     auto block = std::make_shared<StatementListNode>();
//     while (currentToken.type != TokenType::END_OF_FILE) {
//         block->statements.push_back(parseStatement());
//     }
//     return block;
// }

std::shared_ptr<ASTNode> Parser::parseStatement() {
    if (currentToken.type == TokenType::KEYWORD &&
        (currentToken.value == "int" || currentToken.value == "float")) {
        return parseDeclaration();
    } else if (currentToken.type == TokenType::IDENTIFIER) {
        return parseAssignment();
    } else {
        std::cerr << "Syntax Error: Unexpected token '" << currentToken.value << "' in statement\n";
        exit(1);
    }
}

std::shared_ptr<ASTNode> Parser::parseDeclaration() {
    std::string type = currentToken.value;
    advance();

    if (currentToken.type != TokenType::IDENTIFIER) {
        std::cerr << "Expected identifier in declaration\n";
        exit(1);
    }

    std::string varName = currentToken.value;
    advance();
    expect(TokenType::SYMBOL, ";");

    return std::make_shared<DeclarationNode>(type, varName);
}

std::shared_ptr<ASTNode> Parser::parseAssignment() {
    std::string varName = currentToken.value;
    advance();
    expect(TokenType::SYMBOL, "=");
    auto expr = parseExpression();
    expect(TokenType::SYMBOL, ";");

    return std::make_shared<AssignmentNode>(varName, expr);
}

std::shared_ptr<ASTNode> Parser::parseExpression() {
    auto node = parseTerm();
    while (currentToken.value == "+" || currentToken.value == "-") {
        std::string op = currentToken.value;
        advance();
        node = std::make_shared<BinOpNode>(node, op, parseTerm());
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parseTerm() {
    auto node = parseFactor();
    while (currentToken.value == "*" || currentToken.value == "/") {
        std::string op = currentToken.value;
        advance();
        node = std::make_shared<BinOpNode>(node, op, parseFactor());
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parseFactor() {
    if (currentToken.type == TokenType::NUMBER) {
        auto node = std::make_shared<NumberNode>(currentToken.value);
        advance();
        return node;
    }

    if (currentToken.type == TokenType::IDENTIFIER) {
        auto node = std::make_shared<VariableNode>(currentToken.value);
        advance();
        return node;
    }

    if (currentToken.value == "(") {
        advance();
        auto node = parseExpression();
        expect(TokenType::SYMBOL, ")");
        return node;
    }

    std::cerr << "Unexpected token in expression: " << currentToken.value << "\n";
    exit(1);
}
