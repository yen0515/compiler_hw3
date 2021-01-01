#include "AST/read.hpp"

// TODO
ReadNode::ReadNode(const uint32_t line, const uint32_t col,
                    Node _var_ref)
    : AstNode{line, col}, var_ref(_var_ref) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReadNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("read statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void ReadNode::visitChildNodes() {
    if(var_ref!=nullptr){
        this->var_ref->spacecounter = this->spacecounter+1;
        this->var_ref->print();
    }
}
