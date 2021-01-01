#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"

class FunctionNode : public AstNode {
  public:
    FunctionNode(const uint32_t line, const uint32_t col,
                 std::string f_name, std::vector <NodeWithTypeList*>* _argvec,
                 VariableInfo *_returntype, Node _comp_node,  
                 std::vector <VariableInfo*> _arglist);
    ~FunctionNode() = default;

    void print() override;

    void visitChildNodes();

    std::string get_returntype();
    std::string get_argtype();
    //void setspace(int newspace);

  private:
    std::string name;
    std::vector <NodeWithTypeList*>* argvec;
    VariableInfo *returntype;
    Node comp_node;
    std::vector <VariableInfo*> arglist; 
    std::string returntype_str;
    std::string argtype;
    //int space_counter;
};

#endif
