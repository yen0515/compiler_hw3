#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line, const uint32_t col,
                                            Nodevec *_decllist , Nodevec *_stmtlist)
    : AstNode{line, col}, decllist(_decllist), stmtlist(_stmtlist) {}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("compound statement <line: %u, col: %u>\n",
    location.line, location.col);

    visitChildNodes();
}



void CompoundStatementNode::visitChildNodes() {
    if(decllist!=nullptr){
        for(int i=0;i<this->decllist->size();i++){
            //std::printf("  ");
            (*this->decllist)[i]->spacecounter = this->spacecounter+1;
            (*this->decllist)[i]->print();
        }
    }

    if(stmtlist!=nullptr){
        for(int i=0;i<this->stmtlist->size();i++){
            (*this->stmtlist)[i]->spacecounter = this->spacecounter+1;
            (*this->stmtlist)[i]->print();
        }
    }
}
