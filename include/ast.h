#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>

struct ASTNode {
    virtual ~ASTNode() = default;
};

// Number literal like 5, 3
struct NumberNode : ASTNode {
    std::string value;
    NumberNode(const std::string& val) : value(val) {}
};

// Variable like "a"
struct VariableNode : ASTNode {
    std::string name;
    VariableNode(const std::string& n) : name(n) {}
};

// Binary expression like a + b
struct BinOpNode : ASTNode {
    std::string op;
    std::shared_ptr<ASTNode> left, right;
    BinOpNode(std::shared_ptr<ASTNode> l, const std::string& o, std::shared_ptr<ASTNode> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
};

// Assignment like a = 5 + 2;
struct AssignmentNode : ASTNode {
    std::string varName;
    std::shared_ptr<ASTNode> expr;
    AssignmentNode(const std::string& n, std::shared_ptr<ASTNode> e)
        : varName(n), expr(std::move(e)) {}
};

// Declaration like int a;
struct DeclarationNode : ASTNode {
    std::string type;
    std::string varName;
    DeclarationNode(const std::string& t, const std::string& n)
        : type(t), varName(n) {}
};

// List of statements
struct StatementListNode : ASTNode {
    std::vector<std::shared_ptr<ASTNode>> statements;
};

#endif
