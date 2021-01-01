#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"

class FunctionInvocationNode : public ExpressionNode {
  public:
    FunctionInvocationNode(const uint32_t line, const uint32_t col,
                           std::string f_name, Nodevec *_exp_list);
    ~FunctionInvocationNode() = default;

    //const char *getNameCString() const;

    void print() override;
    void visitChildNodes();

  private:
    std::string name;
    Nodevec *exp_list;
};

#endif
