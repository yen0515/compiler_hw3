#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"

class IfNode : public AstNode {
  public:
    IfNode(const uint32_t line, const uint32_t col,
           Node _condstmt, Node _comp_if, Node _comp_else);
    ~IfNode() = default;

    void print() override;
    void visitChildNodes();

  private:
    Node condstmt;
    Node comp_if;
    Node comp_else;
};

#endif
