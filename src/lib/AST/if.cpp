#include "AST/if.hpp"

// TODO
IfNode::IfNode(const uint32_t line, const uint32_t col,
                Node _condstmt, Node _comp_if, Node _comp_else)
    : AstNode{line, col}, condstmt(_condstmt), comp_if(_comp_if), comp_else(_comp_else) {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("if statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void IfNode::visitChildNodes() {
    if(this->condstmt!=nullptr){
        this->condstmt->spacecounter = this->spacecounter+1;
        this->condstmt->print();
    }
    if(this->comp_if!=nullptr){
        this->comp_if->spacecounter = this->spacecounter+1;
        this->comp_if->print();
    }
    if(this->comp_else!=nullptr){
        this->comp_else->spacecounter = this->spacecounter+1;
        this->comp_else->print();
    }
}
