#ifndef __AST_RETURN_NODE_H
#define __AST_RETURN_NODE_H

#include "AST/ast.hpp"

class ReturnNode : public AstNode {
  public:
    ReturnNode(const uint32_t line, const uint32_t col,
               Node _return_exp);
    ~ReturnNode() = default;

    void print() override;
    void visitChildNodes();

  private:
    Node return_exp;
};

#endif
