#include "ast_printer.h"
#include <iostream>

static void printIndent(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
}

void printAST(const std::shared_ptr<ASTNode>& node, int indent) {
    if (!node) return;

    if (auto num = dynamic_cast<NumberNode*>(node.get())) {
        printIndent(indent);
        std::cout << "Number: " << num->value << "\n";

    } else if (auto var = dynamic_cast<VariableNode*>(node.get())) {
        printIndent(indent);
        std::cout << "Variable: " << var->name << "\n";

    } else if (auto bin = dynamic_cast<BinOpNode*>(node.get())) {
        printIndent(indent);
        std::cout << "BinaryOp: " << bin->op << "\n";
        printAST(bin->left, indent + 1);
        printAST(bin->right, indent + 1);

    } else if (auto assign = dynamic_cast<AssignmentNode*>(node.get())) {
        printIndent(indent);
        std::cout << "Assignment: " << assign->varName << "\n";
        printAST(assign->expr, indent + 1);

    } else if (auto decl = dynamic_cast<DeclarationNode*>(node.get())) {
        printIndent(indent);
        std::cout << "Declaration: " << decl->type << " " << decl->varName << "\n";

    } else if (auto list = dynamic_cast<StatementListNode*>(node.get())) {
        printIndent(indent);
        std::cout << "Program:\n";

        for (const auto& stmt : list->statements) {
            printAST(stmt, indent + 1);  // RECURSION here
        }

    } else {
        printIndent(indent);
        std::cout << "<Unknown Node>\n";
    }
}
