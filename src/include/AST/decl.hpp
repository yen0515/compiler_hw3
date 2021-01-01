#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include "AST/ast.hpp"
#include <vector>
#include "AST/variable.hpp"

class DeclNode : public AstNode {
  public:
    // variable declaration
    DeclNode(const uint32_t line, const uint32_t col, Nodevec* var_node_vec
             /* TODO: identifiers, type */);

    // constant variable declaration
    //DeclNode(const uint32_t, const uint32_t col
    //         /* TODO: identifiers, constant */);

    ~DeclNode() = default;


    void print() override;
    void visitChildNodes();
    //void setspace(int newspace);

  private:
    // TODO: variables
    Nodevec* var_node_vec;
    int declnum = 0;
    //int space_counter;
};

#endif
