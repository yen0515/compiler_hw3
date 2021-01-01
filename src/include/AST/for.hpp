#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"

class ForNode : public AstNode {
  public:
    ForNode(const uint32_t line, const uint32_t col,
            Node _decl_node, Node _assign_node, Node _const_node,
            Node _comp);
    ~ForNode() = default;

    void print() override;
    void visitChildNodes();

  private:
    Node decl_node;
    Node assign_node;
    Node const_node;
    Node comp;
};

#endif
