#include "AST/print.hpp"

// TODO
PrintNode::PrintNode(const uint32_t line, const uint32_t col,
                    Node _expression )
    : AstNode{line, col}, expression(_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void PrintNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("print statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void PrintNode::visitChildNodes() {
    if(expression!=nullptr){
        this->expression->spacecounter = this->spacecounter+1;
        this->expression->print();
    }
}
