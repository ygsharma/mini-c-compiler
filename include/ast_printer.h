#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "ast.h"
#include <memory>

void printAST(const std::shared_ptr<ASTNode>& node, int indent = 0);

#endif
