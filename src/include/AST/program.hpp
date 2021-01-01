#ifndef __AST_PROGRAM_NODE_H
#define __AST_PROGRAM_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"



class ProgramNode : public AstNode {
  public:
    ProgramNode(const uint32_t line, const uint32_t col,
                std::string p_name, Nodevec *_decllist , 
                Nodevec *_funclist, Node _comp_node
                /* TODO: return type, declarations, functions,
                 *       compound statement */);
    ~ProgramNode() = default;

    // visitor pattern version: const char *getNameCString() const; 

    void print() override;

    void visitChildNodes();

    //void setspace(int newspace);

  private:
    std::string name;
    Nodevec *decllist;
    Nodevec *funclist;
    Node comp_node;
    //int space_counter = 0;
};

#endif
//Nodevec *_funclist