#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,
                                Node _var_ref, Node _expression)
    : AstNode{line, col}, var_ref(_var_ref), expression(_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("assignment statement <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void AssignmentNode::visitChildNodes() {
    if(var_ref!=nullptr){
        this->var_ref->spacecounter = this->spacecounter+1;
        this->var_ref->print();
    }
    if(expression!=nullptr){
        this->expression->spacecounter = this->spacecounter+1;
        this->expression->print();
    }
}
