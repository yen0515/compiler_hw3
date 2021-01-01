#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col,
                                    enumoperator _op, Node _expression)
    : ExpressionNode{line, col}, op(_op), expression(_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("unary operator <line: %u, col: %u> %s\n",
                location.line, location.col, this->getop().c_str());
    //std::printf("no!!! %s\n", this->op_str.c_str());
    visitChildNodes();
}

void UnaryOperatorNode::visitChildNodes() {
    if(expression!=nullptr){
        this->expression->spacecounter = this->spacecounter+1;
        this->expression->print();
    }
}

std::string UnaryOperatorNode::getop(){
    if(this->op == OP_NOT) this->op_str = "not";
    else if(this->op == OP_MINUS) this->op_str = "neg";
    else this->op_str = "error";
    return this->op_str;
}
