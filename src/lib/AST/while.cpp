#include "AST/while.hpp"

// TODO
WhileNode::WhileNode(const uint32_t line, const uint32_t col,
                     Node _condstmt, Node _comp)
    : AstNode{line, col}, condstmt(_condstmt), comp(_comp) {}

// TODO: You may use code snippets in AstDumper.cpp
void WhileNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("while statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void WhileNode::visitChildNodes() {
    if(this->condstmt!=nullptr){
        this->condstmt->spacecounter = this->spacecounter+1;
        this->condstmt->print();
    }
    if(this->comp!=nullptr){
        this->comp->spacecounter = this->spacecounter+1;
        this->comp->print();
    }
}
