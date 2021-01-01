#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

#include <memory>

class BinaryOperatorNode : public ExpressionNode {
  public:
    BinaryOperatorNode(const uint32_t line, const uint32_t col,
                       Node _expression_fir, enumoperator _op,
                       Node _expression_sec);
    ~BinaryOperatorNode() = default;

    void print() override;
    void visitChildNodes();
    std::string getop();

  private:
    enumoperator op;
    Node expression_fir;
    Node expression_sec;
    std::string op_str;
};

#endif
