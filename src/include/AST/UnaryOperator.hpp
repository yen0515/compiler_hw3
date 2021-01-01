#ifndef __AST_UNARY_OPERATOR_NODE_H
#define __AST_UNARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

class UnaryOperatorNode : public ExpressionNode {
  public:
    UnaryOperatorNode(const uint32_t line, const uint32_t col,
                      enumoperator _op, Node _expression);
    ~UnaryOperatorNode() = default;

    void print() override;
    void visitChildNodes();
    std::string getop();

  private:
    std::string op_str;
    enumoperator op;
    Node expression;
};

#endif
