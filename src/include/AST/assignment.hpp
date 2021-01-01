#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"

class AssignmentNode : public AstNode {
  public:
    AssignmentNode(const uint32_t line, const uint32_t col,
                    Node _var_ref, Node _expression
                   /* TODO: variable reference, expression */);
    ~AssignmentNode() = default;

    void print() override;
    
    void visitChildNodes();
    
  private:
    Node var_ref;
    Node expression;

};

#endif
