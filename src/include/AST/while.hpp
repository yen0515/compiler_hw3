#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"

class WhileNode : public AstNode {
  public:
    WhileNode(const uint32_t line, const uint32_t col,
              Node _condstmt, Node _comp);
    ~WhileNode() = default;

    void print() override;
    void visitChildNodes();

  private:
    Node condstmt;
    Node comp;
};

#endif
