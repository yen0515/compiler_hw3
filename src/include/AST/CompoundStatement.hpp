#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"

class CompoundStatementNode : public AstNode {
  public:
    CompoundStatementNode(const uint32_t line, const uint32_t col,
                          Nodevec *_decllist , Nodevec *_stmtlist
                          /* TODO: declarations, statements */);
    ~CompoundStatementNode() = default;

    void print() override;

    void visitChildNodes();

    void getLocation();


  private:
    // TODO: declarations, statements
  Nodevec *decllist;
  Nodevec *stmtlist;
    
};

#endif
