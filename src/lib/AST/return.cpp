#include "AST/return.hpp"

// TODO
ReturnNode::ReturnNode(const uint32_t line, const uint32_t col, Node _return_exp)
    : AstNode{line, col}, return_exp(_return_exp) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReturnNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("return statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void ReturnNode::visitChildNodes() {
    if(this->return_exp!=nullptr){
        this->return_exp->spacecounter = this->spacecounter+1;
        this->return_exp->print();
    }
}
