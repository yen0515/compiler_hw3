#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include <vector>
#include "AST/ConstantValue.hpp"

class VariableNode : public AstNode {
  public:
    VariableNode(const uint32_t line, const uint32_t col,
                 string v_name, VariableInfo *v_type, Node _const_node
                 /* TODO: variable name, type, constant value */);
    ~VariableNode() = default;

    void print() override;

    void visitChildNodes();

    std::string gettype();

  private:
    std::string name;
    std::string var_type;
    VariableInfo* type;
    Node const_node;
    
    // TODO: variable name, type, constant value
};

#endif
