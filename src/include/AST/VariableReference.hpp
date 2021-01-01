#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"

class VariableReferenceNode : public ExpressionNode {
  public:
    // normal reference
    VariableReferenceNode(const uint32_t line, const uint32_t col,
                          std::string v_name, Nodevec *_arr_ref);
    // array reference
    // VariableReferenceNode(const uint32_t line, const uint32_t col
    //                       /* TODO: name, expressions */);
    ~VariableReferenceNode() = default;

    void print() override;
    void visitChildNodes();

  private:
    std::string name;
    Nodevec *arr_ref;
};

#endif
