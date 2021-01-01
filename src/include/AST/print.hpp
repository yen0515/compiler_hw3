#ifndef __AST_PRINT_NODE_H
#define __AST_PRINT_NODE_H

#include "AST/ast.hpp"

class PrintNode : public AstNode {
  public:
    PrintNode(const uint32_t line, const uint32_t col,
              Node _expression);
    ~PrintNode() = default;

    void print() override;

    void visitChildNodes();

  private:
    Node expression;
};

#endif
