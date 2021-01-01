#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"
#include <string>

class ConstantValueNode : public ExpressionNode {
  public:
    ConstantValueNode(const uint32_t line, const uint32_t col, VariableInfo *_const_val
                      /* TODO: constant value */);
    
    ~ConstantValueNode() = default;

    void print() override;

    std::string getval();

  private:
    // TODO: constant value
    VariableInfo *const_val;
    std::string val;
};

#endif
