#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <vector>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct NumberNode : public ASTNode {
    std::string value;
    NumberNode(const std::string& val) : value(val) {}
};

struct VariableNode : public ASTNode {
    std::string name;
    VariableNode(const std:: string& n) : name(n) {}
};

struct BinOpNode : public ASTNode {
    std:: string op;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    BinOpNode(std::string& o, std::shared_ptr<ASTNode> l, std::shared_ptr<ASTNode> r) : op(o), left(l), right(r) {}
};

struct AssignmentNode : public ASTNode {
    std::string varName;
    std::shared_ptr<ASTNode> expr;

    AssignmentNode(const std::string& n, std::shared_ptr<ASTNode> e) : varName(n), expr(e) {}
};

#endif